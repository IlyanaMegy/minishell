/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:50:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/22 12:14:36 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	sep_is_doubled(t_token *token_node)
{
	if ((token_node->type > PIPE
			&& token_node->next
			&& token_node->next->type > PIPE)
		|| (token_node->type == PIPE
			&& (!token_node->prev || !token_node->next))
		|| (token_node->type == PIPE && !token_node->prev && !token_node->next))
		return (true);
	return (false);
}

static bool	sep_is_before_newline(t_token *token_node)
{
	if ((token_node->type > PIPE && !token_node->next))
		return (true);
	return (false);
}

static bool	check_sep(t_token *token_node)
{
	char	*value;

	if (sep_is_doubled(token_node))
	{
		if ((token_node->type == PIPE
				&& (!token_node->prev || !token_node->next))
			|| (token_node->type == PIPE
				&& !token_node->prev && !token_node->next))
			value = token_node->value;
		else
			value = token_node->next->value;
		err_syntax(ERR_SYNTAX, value);
		return (false);
	}
	else if (sep_is_before_newline(token_node))
	{
		err_syntax(ERR_SYNTAX, "newline");
		return (false);
	}
	return (true);
}

bool	check_syntax(t_token *token_node)
{
	while (token_node)
	{
		if (!check_sep(token_node))
			return (single_exit_s(2, ADD), false);
		else if (ft_strcmp(token_node->value, "echo") == 0
			&& (!token_node->next
				|| (token_node->next->type >= PIPE && !token_node->next->next)))
		{
			ft_printf("\n");
			return (single_exit_s(ERR_NOCMD, ADD), false);
		}
		token_node = token_node->next;
	}
	return (true);
}
