/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:03:32 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/19 22:33:31 by ilymegy          ###   ########.fr       */
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

/**
 * @note   get io_expanded_value
 * @param  io: t_io_cmd linked list
 * @retval None
*/
void	get_io_expanded_value(t_io_cmd *io)
{
	char	**io_path_d;

	io_path_d = malloc(sizeof(char *) * 2);
	io_path_d[0] = ft_strdup(io->path);
	io_path_d[1] = NULL;
	io->expanded_value = expander(io_path_d);
	free_tab(io_path_d);
}

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
	int			pid;

	if (cmd->args)
		cmd->expanded_args = expander(cmd->args);
	io = cmd->io_list;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(fd);
			data->signint_child = true;
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				come_heredoc(data, io, fd);
			if (quit_da_cmd(data, fd, &pid))
				return ;
			io->here_doc = fd[0];
		}
		else
			get_io_expanded_value(io);
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
