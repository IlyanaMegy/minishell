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
 * @note   get expanded heredoc delimiter
 * @param  io_cmd: t_io_cmd linked list
 * @retval None
*/
void	get_expander_heredoc_delim(t_io_cmd *io_cmd)
{
	io_cmd->expanded_value = malloc(sizeof(char *) * 2);
	if (!io_cmd->expanded_value)
		return ;
	io_cmd->expanded_value[0] = expand_heredoc_delim(io_cmd->path);
	io_cmd->expanded_value[1] = NULL;
	return ;
}

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
	get_expander_heredoc_delim(io);
	quotes = io->expanded_value[0];
	// ft_printf("delim = %s\n\n", quotes);
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_isdelimiter(io->expanded_value[0], line))
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
static void	init_da_cmd(t_data *data, t_cmd *cmd)
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
			data->signint_child = true;
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				come_heredoc(data, io, fd);
			if (quit_da_cmd(data, fd, &pid))
				return ;
			io->here_doc = fd[0];
		}
		else
			io->expanded_value = expand(io->path);
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
