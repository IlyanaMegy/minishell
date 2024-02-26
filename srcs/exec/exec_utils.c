/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:39:39 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/17 17:32:08 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   reset stdin and stdout if not piped
 * @param  data: t_data linked list
 * @param  piped: is it piped or not
 * @retval None
*/
void	reset_stds(t_data *data, bool piped)
{
	if (piped)
		return ;
	dup2(data->stdin, 0);
	dup2(data->stdout, 1);
	close(data->stdin);
	close(data->stdout);
}

/**
 * @note   let's free everything before exit with the right status
 * @param  data: t_data linked list to free
 * @param  status: exit status
 * @param  env: environment 2D array to free
 * @retval None
*/
void	get_out(t_data *data, int status, char **env, int *status_waitpid)
{
	if (env)
		free_tab(env);
	clean_program(data);
	*status_waitpid = status;
	exit(status);
}

/**
 * @note   check redirections of the given command
 * @param  cmd: current command
 * @retval exit status
*/
int	check_redir(t_cmd *cmd)
{
	t_io_cmd	*cmd_io;
	int			status;

	cmd_io = cmd->io_list;
	while (cmd_io)
	{
		if (cmd_io->type == IO_OUT && open_out(cmd_io, &status) != 0)
			return (status);
		else if (cmd_io->type == IO_IN && open_in(cmd_io, &status) != 0)
			return (status);
		else if (cmd_io->type == IO_APPEND && open_append(cmd_io, &status) != 0)
			return (status);
		else if (cmd_io->type == IO_HEREDOC)
		{
			dup2(cmd_io->here_doc, 0);
			close(cmd_io->here_doc);
		}
		cmd_io = cmd_io->next;
	}
	return (ENO_SUCCESS);
}

/**
 * @note   get right exit status
 * @param  status:
 * @retval exit status
*/
int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

/**
 * @note   swap fd[2] and fd[0] and close them
 * @param  fd: given fds
 * @retval None
*/
void	swap_pipes(int fd[3])
{
	dup2(fd[0], fd[2]);
	close(fd[0]);
	close(fd[1]);
}
