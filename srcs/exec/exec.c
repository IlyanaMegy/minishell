/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:24 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/13 16:22:25 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   executing pipe child
 * @param  data: t_data linked list 
 * @param  fd[2]: pipes
 * @param  dir: LEFT or RIGHT command
 * @retval None
*/
static void	exec_pipe_child(t_data *data, int fd[2], t_cmd_direction dir)
{
	if (dir == LEFT)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (dir == RIGHT)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	executie(data, true);
	clean_program(data);
	exit(single_exit_s(0, GET));
}

/**
 * @note   executing when pipe
 * @param  data: t_data linked list
 * @retval exit status
*/
static int	exec_pipe(t_data *data)
{
	int	status;
	int	fd[2];
	int	pid_first;
	int	pid_sec;

	// signint_child = true
	if (pipe(fd) < 0)
		return (ft_putstr_fd("__ERROR_PIPE__:\nError pipe.\n", 2), 1);
	pid_first = fork();
	if (pid_first < 0)
		return (ft_putchar_fd("__ERROR_FORK__:\nError fork.\n", 2), 1);
	if (!pid_first)
		exec_pipe_child(data, fd, LEFT);
	else
	{
		pid_sec = fork();
		if (pid_sec < 0)
			return (ft_putchar_fd("__ERROR_FORK__:\nError fork.\n", 2), 1);
		if (!pid_sec)
			exec_pipe_child(data, fd, RIGHT);
		else
			return (close_n_wait(fd, pid_first, pid_sec));
		return (ENO_GENERAL);
	}
}

/**
 * @note   execution of child
 * @param  data: t_data linked list
 * @retval exit status
*/
static int	exec_child(t_data *data)
{
	int		fork_pid;
	int		status;
	char	*path;
	char	**env;

	// signint_child = true
	env = env_to_tab(single_env(NULL, GET));
	fork_pid = fork();
	if (fork_pid < 0)
		return (ft_putchar_fd("__ERROR_FORK__:\nError fork.\n", 2), 1);
	if (!fork_pid)
	{
		status = check_redir(data);
		if (status != ENO_SUCCESS)
			get_out(data, ENO_GENERAL, env);
		path = get_path(data->cmd->args[0]);
		if (!path)
			get_out(data, single_exit_s(0, GET), env);
		if (execve(path, data->cmd->args, env) == -1)
			return (free(path), get_out(data, single_exit_s(0, GET), env), 1);
		free(path);
	}
	waitpid(fork_pid, &status, 0);
	// signint_child = false
	return (free_tab(env), get_exit_status(status));
}

/**
 * @note   execution as simple command
 * @param  *data: t_data linked list
 * @param  piped: is it piped ?
 * @retval exit status
*/
int	exec_simple_cmd(t_data *data, bool piped)
{
	if (!data->cmd->args)
	{
		single_exit_s(check_redir(data->cmd), ADD);
		return (reset_stds(piped), (single_exit_s(0, GET) && ENO_GENERAL));
	}
	else if (is_builtin(data->cmd->args[0]))
	{
		single_exit_s(check_redir(data->cmd), ADD);
		if (single_exit_s(0, GET) != ENO_SUCCESS)
			return (reset_stds(piped), ENO_GENERAL);
		single_exit_s(exec_builtin(data), ADD);
		return (reset_stds(piped), single_exit_s(0, GET));
	}
	else
		return (exec_child(data));
}

/**
 * @note   How will we execute it ?
 * @param  *data: t_data linked list
 * @retval None
*/
void	executie(t_data *data, bool piped)
{
	if (!data->cmd)
		single_exit_s(1, ADD);
	if (data->cmd->next)
		single_exit_s(exec_pipe(data), ADD);
	else
		single_exit_s(exec_simple_cmd(data, piped), ADD);
	single_exit_s(ENO_GENERAL, ADD);
}
