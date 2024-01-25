/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:44:39 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/25 17:06:09 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_io_type	get_io_type(t_token_type type)
{
	if (type == INPUT)
		return (IO_IN);
	else if (type == TRUNC)
		return (IO_OUT);
	else if (type == HEREDOC)
		return (IO_HEREDOC);
	else if (type == APPEND)
		return (IO_APPEND);
	return (-1);
}

static t_token	*get_next_token(t_token *token)
{
	if (token->next->next
		&& (token->next->next->type == WORD
			|| token->next->next->type >= PIPE))
		return (token->next->next);
	else
		return (token->next);
}

bool	handle_redir(t_cmd **last_cmd, t_token **token_lst, t_token_type type)
{
	t_cmd		*cmd;
	t_token		*token;
	t_io_cmd	*last_io;

	token = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	if (!init_io_cmd(&cmd))
		return (false);
	last_io = (*cmd).io_list;
	while (last_io && last_io->next)
		last_io = last_io->next;
	last_io->path = ft_strdup(token->next->value);
	if (!last_io->path)
		return (false);
	last_io->type = get_io_type(type);
	token = get_next_token(token);
	*token_lst = token;
	return (true);
}
