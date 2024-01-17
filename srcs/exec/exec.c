/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:24 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/15 19:42:14 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   executing pipe child
 * @param  data: t_data linked list
 * @param  cmd : current command to execute
 * @param  fd[2]: pipes
 * @param  dir: LEFT or RIGHT command
 * @retval None
*/
static void	exec_pipe_child(t_data *data, t_cmd *cmd, int fd[2],
		t_cmd_direction dir)
{
	if (dir == LEFT)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_simple_cmd(data, cmd, true);
	}
	else if (dir == RIGHT)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		executie(data, cmd, true);
	}	
	clean_program(data);
	exit(single_exit_s(0, GET));
}

/**
 * @note   executing when pipe
 * @param  data: t_data linked list
 * @param  cmd : current command to execute
 * @retval exit status
*/
static int	exec_pipe(t_data *data, t_cmd *cmd)
{
	int	fd[2];
	int	pid_first;
	int	pid_sec;

	// signint_child = true
	if (pipe(fd) != 0)
		return (ft_putstr_fd(strerror(3), 2), 3);
	// return (ft_putstr_fd("__ERROR_PIPE__:\nError pipe.\n", 2), 1);
	pid_first = fork();
	if (pid_first == -1)
		return (ft_putstr_fd("__ERROR_FORK__:\nError fork.\n", 2), 4);
	if (!pid_first)
		exec_pipe_child(data, cmd, fd, LEFT);
	else
	{
		pid_sec = fork();
		if (pid_sec == -1)
			return (ft_putstr_fd("__ERROR_FORK__:\nError fork.\n", 2), 4);
		if (!pid_sec)
			exec_pipe_child(data, cmd->next, fd, RIGHT);
		else
			return (close_n_wait(fd, pid_first, pid_sec));
	}
	return (ENO_GENERAL);
}

/**
 * @note   execution of child
 * @param  data: t_data linked list
 * @param  cmd : current command to execute
 * @param  fork_pid : recently forked variable
 * @retval exit status
*/
static int	exec_child(t_data *data, t_cmd *cmd, int fork_pid)
{
	int		status;
	t_path	path;
	char	**env;

	// signint_child = true
	env = env_to_tab(single_env(NULL, GET));
	if (!env)
		return (ENO_GENERAL);
	if (!fork_pid)
	{
		status = check_redir(cmd);
		if (status != ENO_SUCCESS)
			get_out(data, ENO_GENERAL, env);
		path = get_path(cmd->args[0]);
		if (path.err.no != ENO_SUCCESS)
			(err_handler(path.err.msg, path.err.cause), get_out(data,
						single_exit_s(path.err.no, ADD), env));
		if (execve(path.path, cmd->args, env) == -1)
			return (free(path.path), get_out(data, single_exit_s(0, GET), env),
				1);
		free(path.path);
	}
	waitpid(fork_pid, &status, 0);
	// signint_child = false
	return (free_tab(env), get_exit_status(status));
}

/**
 * @note   execution as simple command
 * @param  data: t_data linked list
 * @param  piped: is it piped ?
 * @param  cmd: current command to execute
 * @retval exit status
*/
int	exec_simple_cmd(t_data *data, t_cmd *cmd, bool piped)
{
	int	fork_pid;

	if (!cmd->args)
	{
		single_exit_s(check_redir(cmd), ADD);
		reset_stds(data, piped);
		return ((single_exit_s(0, GET) && ENO_GENERAL));
	}
	else if (is_builtin(cmd->args[0]))
	{
		single_exit_s(check_redir(cmd), ADD);
		if (single_exit_s(0, GET) != ENO_SUCCESS)
			return (reset_stds(data, piped), ENO_GENERAL);
		single_exit_s(exec_builtin(data, cmd), ADD);
		return (reset_stds(data, piped), single_exit_s(0, GET));
	}
	else
	{
		fork_pid = fork();
		if (fork_pid < 0)
			return (ft_putstr_fd("__ERROR_FORK__:\nError fork.\n", 2), 4);
		return (exec_child(data, cmd, fork_pid));
	}
}

/**
 * @note   How will we execute it ?
 * @param  data: t_data linked list
 * @param  cmd : current command to execute
 * @retval None
*/
void	executie(t_data *data, t_cmd *cmd, bool piped)
{
	if (!cmd)
		single_exit_s(ENO_GENERAL, ADD);
	if (cmd->next)
		single_exit_s(exec_pipe(data, cmd), ADD);
	else
		single_exit_s(exec_simple_cmd(data, cmd, piped), ADD);
}
