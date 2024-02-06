/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:03:32 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/06 10:04:40 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

	signal(SIGINT, heredoc_handler);
	quotes = io->path;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		if (g_sig_exit)
			(clean_program(data), g_sig_exit = 0, exit(2));
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
		free(line);
	}
	(clean_program(data), exit(0));
}

/**
 * @note   get expanded value of commands
 * @param  io: t_cmd linked list
 * @retval None
*/
void	get_expanded_value(t_cmd *cmd)
{
	char	*joined_args;

	joined_args = ft_strsjoin(cmd->args, " ");
	cmd->expanded_args = expand(joined_args);
	free(joined_args);
}

/**
 * @note   initializing t_cmd lst and handling here_docs
 * @param  data: t_data linked list
 * @param  cmd: t_cmd linked list
 * @retval None
*/
static bool	init_da_cmd(t_data *data, t_cmd *cmd)
{
	t_io_cmd	*io;
	int			fd[2];
	int			pid;

	if (cmd->args)
		get_expanded_value(cmd);
	io = cmd->io_list;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(fd);
			single_sign_child(true, ADD);
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				come_heredoc(data, io, fd);
			if (quit_da_cmd(fd, &pid))
				return (false);
			io->here_doc = fd[0];
		}
		else
			io->expanded_value = expand(io->path);
		io = io->next;
	}
	return (true);
}

/**
 * @note   initializing t_cmd lst
 * @param  data: t_data linked list
 * @param  cmd: t_cmd linked list
 * @retval None
*/
bool	init_cmdlst(t_data *data, t_cmd *cmd)
{
	if (!cmd)
		return (false);
	if (cmd->next)
	{
		if (!init_da_cmd(data, cmd))
			return (false);
		init_cmdlst(data, cmd->next);
	}
	else
	{
		if (!init_da_cmd(data, cmd))
			return (false);
	}
	return (true);
}
