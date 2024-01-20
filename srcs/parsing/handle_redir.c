/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:44:39 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/20 13:03:18 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*generate_name(void)
{
	static int	i = 0;
	char		*n;
	char		*name;

	n = ft_itoa(i);
	if (!n)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, n);
	if (!name)
		return (NULL);
	free_ptr(n);
	i++;
	return (name);
}

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

static char	*get_io_path(t_token **token, t_token_type type)
{
	if (type == HEREDOC)
		return (generate_name());
	else
		return (ft_strdup((*token)->next->value));
}

static t_token	*get_next_token(t_token **token)
{
	if ((*token)->next->next
		&& ((*token)->next->next->type == WORD
			|| (*token)->next->next->type == PIPE))
		return ((*token)->next->next);
	else
		return ((*token)->next);
}

bool	handle_redir(t_cmd **last_cmd, t_token **token_lst, t_token_type type)
{
	t_token		*token;
	t_cmd		*cmd;

	token = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	if (!init_io_cmd(&cmd))
		return (false);
	cmd->io_list->path = get_io_path(&token, type);
	if (!cmd->io_list->path)
		return (false);
	cmd->io_list->type = get_io_type(type);
	token = get_next_token(&token);
	*token_lst = token;
	return (true);
}
