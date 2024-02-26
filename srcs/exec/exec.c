/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:24 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/17 22:17:39 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   close last heredoc's fd if current cmd is heredoc
 * @param  cmd: given command 
 * @retval None
*/
void	ignore_last_heredoc(t_cmd *cmd, t_io_cmd *io)
{
	t_io_cmd	*io_prev;
	t_cmd		*c;

	c = cmd->prev;
	while (c)
	{
		if (c->io_list && c->io_list->type == IO_HEREDOC)
			close(c->io_list->here_doc);
		c = c->prev;
	}
	io_prev = io->prev;
	while (io_prev)
	{
		if (io_prev->type == IO_HEREDOC)
			close(io_prev->here_doc);
		io_prev = io_prev->prev;
	}
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

	set_sig_child();
	if (!fork_pid)
	{
		if (cmd_is_dot(cmd->expanded_args[0]))
			get_out(data, ENO_MISS_CMD, NULL, &status);
		if (cmd_is_dir(cmd->expanded_args[0]))
			get_out(data, ENO_CANT_EXEC, NULL, &status);
		env = env_to_tab(single_env(NULL, GET));
		if (!env)
			get_out(data, ENO_GENERAL, NULL, &status);
		if (check_redir(cmd) != ENO_SUCCESS)
			get_out(data, ENO_GENERAL, env, &status);
		path = get_path(data, cmd->expanded_args[0]);
		if (path.err.no != ENO_SUCCESS)
			(err_handler(path.err.msg, path.err.cause),
				get_out(data, single_exit_s(path.err.no, ADD), env, &status));
		if (execve(path.path, cmd->expanded_args, env) == -1)
			get_out(data, single_exit_s(1, ADD), env, &status);
	}
	waitpid(fork_pid, &status, 0);
	return (close_n_exit_s(data, cmd, status));
}

/**
 * @note   execution as simple command
 * @param  data: t_data linked list
 * @param  cmd: current command to execute
 * @retval exit status
 */
static int	exec_simple_cmd(t_data *data, t_cmd *cmd, bool piped)
{
	int	fork_pid;

	if (!cmd->expanded_args)
	{
		single_exit_s(check_redir(cmd), ADD);
		reset_stds(data, piped);
		return ((single_exit_s(0, GET) && ENO_GENERAL));
	}
	else if (is_builtin(cmd->expanded_args[0]))
	{
		single_exit_s(check_redir(cmd), ADD);
		if (single_exit_s(0, GET) != ENO_SUCCESS)
			return (reset_stds(data, piped), ENO_GENERAL);
		single_exit_s(exec_builtin(data, cmd), ADD);
		return (reset_stds(data, piped), single_exit_s(0, GET));
	}
	else
	{
		signal(SIGINT, SIG_IGN);
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
		single_exit_s(exec_pipe(data), ADD);
	else
		single_exit_s(exec_simple_cmd(data, cmd, piped), ADD);
}
