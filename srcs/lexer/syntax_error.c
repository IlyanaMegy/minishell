/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:50:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/19 16:30:45 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	pipe_is_invalid(t_token *token_node)
{
	if ((token_node->type > PIPE
			&& token_node->next && token_node->next->type == PIPE
			&& token_node->next->next && token_node->next->next->type > PIPE)
		|| (token_node->type > PIPE
			&& token_node->next && token_node->next->type > PIPE
			&& token_node->next->next && token_node->next->next->type == PIPE)
		|| (token_node->type == PIPE
			&& token_node->next && token_node->next->type == PIPE)
		|| (token_node->type == PIPE
			&& (!token_node->prev || !token_node->next))
		|| (token_node->type == PIPE && !token_node->prev && !token_node->next))
		return (true);
	return (false);
}

static bool	is_unexpected_token(t_token *token_node)
{
	if (pipe_is_invalid(token_node))
		return (true);
	else if ((token_node->type == INPUT
			&& token_node->next
			&& token_node->next->type == TRUNC
			&& !token_node->next->next)
		|| (token_node->type == HEREDOC
			&& token_node->next
			&& token_node->next->type == INPUT))
		return (false);
	else if ((token_node->type > PIPE
			&& token_node->next
			&& token_node->next->type > PIPE))
		return (true);
	return (false);
}

static bool	is_before_newline(t_token *token_node)
{
	if ((token_node->type == INPUT
			&& token_node->next
			&& token_node->next->type == TRUNC
			&& !token_node->next->next)
		|| (token_node->type == HEREDOC
			&& token_node->next
			&& token_node->next->type == INPUT)
		|| (token_node->type > PIPE && !token_node->next))
		return (true);
	return (false);
}

static bool	check_sep(t_token *token_node)
{
	char	*value;

	if (is_unexpected_token(token_node))
	{
		if ((token_node->type == PIPE
				&& (!token_node->prev || !token_node->next))
			|| (token_node->type == PIPE
				&& !token_node->prev && !token_node->next))
			value = token_node->value;
		else if ((token_node->type > PIPE
				&& token_node->next && token_node->next->type > PIPE
				&& token_node->next->next
				&& token_node->next->next->type == PIPE))
			value = token_node->next->next->value;
		else
			value = token_node->next->value;
		err_syntax(value);
		return (false);
	}
	else if (is_before_newline(token_node))
	{
		err_syntax("newline");
		return (false);
	}
	return (true);
}

bool	check_syntax(t_token *token)
{
	t_token	*first;

	first = token;
	while (token)
	{
		if (!check_sep(token))
			return (single_exit_s(2, ADD), false);
		token = token->next;
	}
	if (ft_strcmp(first->value, "./minishell") == 0)
		return (single_exit_s(0, ADD), false);
	return (true);
}
