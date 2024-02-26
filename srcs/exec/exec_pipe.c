/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:09:33 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/22 12:54:07 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   do wait and display child's error if there is
 * @param  data: t_data linked list
 * @retval exit status
*/
static int	ft_waitpid(t_data *data)
{
	t_cmd	*c;
	int		err;

	c = data->cmd;
	while (c)
	{
		waitpid(c->pid, &err, 0);
		if (c->expanded_args && !is_builtin(c->expanded_args[0])
			&& !cmd_is_dot(c->expanded_args[0])
			&& !cmd_is_dir(c->expanded_args[0]))
		{
			c->path_err = get_path(data, c->expanded_args[0]);
			if (c->path_err.err.no != ENO_SUCCESS)
				err_handler(c->path_err.err.msg, c->path_err.err.cause);
			if (c->path_err.path)
				free_ptr(c->path_err.path);
		}
		c = c->next;
	}
	return (err);
}

/**
 * @note   simply close fds
 * @param  fd[3]: files descriptors
 * @retval None
*/
static void	ft_close_all(int fd[3])
{
	char	buf;
	int		i;

	i = 4;
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	while (i < 150)
	{
		if (read(i, &buf, 0) != -1)
			close(i);
		i++;
	}
}

/**
 * @brief
 * @note   handle when no cmd, builtins, cmd is dot or dir
 * @param  data: t_data linked list
 * @param  cmd: given command
 * @param  *status: exit status
 * @retval None
*/
static void	handle_weird_cases(t_data *data, t_cmd *cmd, int *status)
{
	if (!cmd->expanded_args)
	{
		if (check_redir(cmd) != ENO_SUCCESS)
			single_exit_s(ENO_GENERAL, ADD);
		clean_program(data);
		exit(single_exit_s(0, GET));
	}
	else if (is_builtin(cmd->expanded_args[0]))
	{
		if (check_redir(cmd) == ENO_SUCCESS)
			single_exit_s(exec_builtin(data, cmd), ADD);
		else
			single_exit_s(ENO_GENERAL, ADD);
		clean_program(data);
		exit(single_exit_s(0, GET));
	}
	if (cmd_is_dot(cmd->expanded_args[0]))
		get_out(data, ENO_MISS_CMD, NULL, status);
	if (cmd_is_dir(cmd->expanded_args[0]))
		get_out(data, ENO_CANT_EXEC, NULL, status);
}

/**
 * @note   execution of child when pipes
 * @param  data: t_data linked list
 * @param  cmd: given command
 * @param  *status: exit status of child process
 * @param  fd[3]: files descriptors
 * @retval None
*/
static void	exec_pipe_child(t_data *data, t_cmd *cmd, int *status, int fd[3])
{
	char	**env;

	if (!cmd->prev)
		dup2(fd[1], STDOUT_FILENO);
	if (!cmd->next)
		dup2(fd[2], STDIN_FILENO);
	else if (cmd->next && cmd->prev)
	{
		dup2(fd[2], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	ft_close_all(fd);
	handle_weird_cases(data, cmd, status);
	env = env_to_tab(single_env(NULL, GET));
	if (!env)
		get_out(data, ENO_GENERAL, NULL, status);
	if (check_redir(cmd) != ENO_SUCCESS)
		get_out(data, ENO_GENERAL, env, status);
	cmd->path_err = get_path(data, cmd->expanded_args[0]);
	if (cmd->path_err.err.no != ENO_SUCCESS)
		get_out(data, single_exit_s(cmd->path_err.err.no, ADD), env, status);
	if (execve(cmd->path_err.path, cmd->expanded_args, env) == -1)
		get_out(data, single_exit_s(1, ADD), env, status);
}

/**
 * @note   execution when pipes
 * @param  data: t_data linked list
 * @retval exit status
*/
int	exec_pipe(t_data *data)
{
	t_cmd	*c;
	int		fd[3];
	int		status;

	status = 0;
	c = data->cmd;
	fd[2] = dup(STDIN_FILENO);
	while (c)
	{
		if (pipe(fd) != 0)
			return (ft_putstr_fd("__ERROR_PIPE__:\nError pipe.\n", 2), 3);
		signal(SIGINT, SIG_IGN);
		c->pid = fork();
		if (c->pid == -1)
			return (ft_putstr_fd("__ERROR_FORK__:\nError fork.\n", 2), 4);
		if (!c->pid)
			(set_sig_child(), exec_pipe_child(data, c, &status, fd));
		swap_pipes(fd);
		single_exit_s(close_n_exit_s(data, c, status), ADD);
		c = c->next;
	}
	close(fd[2]);
	status = ft_waitpid(data);
	return (get_exit_status(status));
}
