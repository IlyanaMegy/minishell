/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:39:39 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/11 15:39:41 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	ft_reset_stds(bool piped)
// {
// 	if (piped)
// 		return ;
// 	dup2(g_minishell.stdin, 0);
// 	dup2(g_minishell.stdout, 1);
// }

void	get_out(t_data *data, int status, char **env)
{
	free_tab(env);
	clean_program(data);
	exit (status);
}

int	check_redir(t_data *data)
{
	t_io_cmd	*cmd_io;
	int			status;

	cmd_io = data->cmd->io_list;
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

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	close_n_wait(int fd[2], int p_first, int p_sec)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(p_first, &status, 0);
	waitpid(p_sec, &status, 0);
	// signint_child = false
	return (get_exit_status(status));
}
