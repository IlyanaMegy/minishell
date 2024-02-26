/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:03:32 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/22 12:53:46 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   get expanded heredoc delimiter
 * @param  io_cmd: t_io_cmd linked list
 * @retval None
*/
static void	get_expander_heredoc_delim(t_io_cmd *io_cmd)
{
	signal(SIGINT, heredoc_handler);
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
static void	come_heredoc(t_data *data, t_io_cmd *io, int fd[2])
{
	char	*line;
	char	*quotes;

	get_expander_heredoc_delim(io);
	quotes = io->path;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		catch_sigint_exit(data);
		if (!line && print_heredoc_error())
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
	(clean_program(data), close(fd[1]), close(fd[0]), exit(0));
}

/**
 * @note   get expanded value of commands
 * @param  io: t_cmd linked list
 * @retval false if err malloc, true is ok
*/
static bool	get_expanded_value(t_cmd *cmd)
{
	char	*joined_args;

	joined_args = ft_strsjoin(cmd->args, " ");
	if (!joined_args)
		return (false);
	cmd->expanded_args = expand(joined_args);
	free(joined_args);
	if (!cmd->expanded_args)
		return (false);
	return (true);
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

	if (cmd->args && !get_expanded_value(cmd))
		return (false);
	io = cmd->io_list;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			ignore_last_heredoc(cmd, io);
			(pipe(fd), signal(SIGINT, SIG_IGN));
			pid = fork();
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
		return (init_cmdlst(data, cmd->next));
	}
	else
	{
		if (!init_da_cmd(data, cmd))
			return (false);
	}
	return (true);
}
