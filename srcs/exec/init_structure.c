/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:03:32 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/18 16:03:33 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void	heredoc_sigint_handler(t_data *data, int signum)
// {
// 	(void)signum;
// 	clean_program(data);
// 	exit(SIGINT);
// }

/**
 * @note   handling here_doc
 * @param  data: t_data linked list
 * @param  io: io_cmd lst
 * @param  fd[2]: files descriptors
 * @retval None
*/
void	come_heredoc(t_data *data, t_io_cmd *io, int fd[2])
{
	char	*line;
	char	*quotes;

	// signal(SIGINT, heredoc_sigint_handler);
	quotes = io->path;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_isdelimiter(io->path, line))
			break ;
		if (!*quotes)
			heredoc_expander(line, fd[1]);
		else
		{
			ft_putstr_fd(line, fd[1]);
			ft_putstr_fd("\n", fd[1]);
		}
	}
	clean_program(data);
	exit(0);
}

// static bool	quit_da_cmd(t_data *data, int fd[2], int *pid)
// {
// 	waitpid(*pid, pid, 0);
// 	signal(SIGQUIT, ft_sigquit_handler);
// 	data->signint_child = false;
// 	close(fd[1]);
// 	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
// 		return (true);
// 	return (false);
// }

/**
 * @note   initializing t_cmd lst and handling here_docs
 * @param  data: t_data linked list
 * @param  cmd: t_cmd linked list
 * @retval None
*/
static void	init_da_cmd(t_data *data, t_cmd *cmd)
{
	t_io_cmd	*io;
	int			fd[2];
	char		*args;
	int			pid;

	if (cmd->args)
	{
		args = ft_strsjoin(cmd->args, " ");
		cmd->expanded_args = expander(args);
		free(args);
	}
	io = cmd->io_list;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(fd);
			// data->signint_child = true;
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				come_heredoc(data, io, fd);
			// if (quit_da_cmd(data, fd, &pid))
			// 	return ;
			io->here_doc = fd[0];
		}
		else
			io->expanded_value = expander(io->path);
		io = io->next;
	}
}

/**
 * @note   initializing t_cmd lst
 * @param  data: t_data linked list
 * @param  cmd: t_cmd linked list
 * @retval None
*/
void	init_cmdlst(t_data *data, t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->next)
	{
		init_da_cmd(data, cmd);
		// if (!data->heredoc_sigint)
		init_cmdlst(data, cmd->next);
	}
	else
		init_da_cmd(data, cmd);
}
