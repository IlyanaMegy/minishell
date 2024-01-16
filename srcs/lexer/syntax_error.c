/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:50:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/12 21:16:32 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	sep_is_doubled(t_token *token_node)
{
	if (token_node->next)
	{
		if (((token_node->type > PIPE && token_node->next->type > PIPE)
			&& (token_node->type != INPUT && token_node->next->type != TRUNC))
			|| (token_node->type == INPUT && token_node->next->type == INPUT)
			|| (token_node->type == TRUNC && token_node->next->type == TRUNC))
			return (true);
	}
	return (false);
}

static bool	sep_is_before_newline(t_token *token_node)
{
	if ((token_node->type > PIPE && !token_node->next)
		|| (token_node->type == INPUT && token_node->next->type == TRUNC))
		return (true);
	return (false);
}

static bool	pipe_is_invalid(t_token *token_node)
{
	if (token_node->type == PIPE)
	{
		if ((!token_node->prev)
			|| (!token_node->prev && !token_node->next))
			return (true);
	}
	return (false);
}

static bool	check_sep(t_token *token_node)
{
	if (sep_is_doubled(token_node))
	{
		err_syntax(ERR_SYNTAX, token_node->next->value);
		return (false);
	}
	else if (sep_is_before_newline(token_node))
	{
		err_syntax(ERR_SYNTAX, "newline");
		return (false);
	}
	else if (pipe_is_invalid(token_node))
	{
		err_syntax(ERR_SYNTAX, token_node->value);
		return (false);
	}
	return (true);
}

bool	is_builtin(char *arg)
{
	if (!arg)
		return (false);
	if (!ft_strcmp(arg, "echo")
		|| !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "exit")
		|| !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env"))
		return (true);
	return (false);
}

static bool	check_word(t_token *token_node)
{
	if (!is_builtin(token_node->value))
	{
		err_syntax(ERR_CMD_NOT_FOUND, token_node->value);
		return (false);
	}
	return (true);
}

bool	check_syntax(t_token **token_lst)
{
	t_token	*token;

	token = *token_lst;
	while (*token_lst)
	{
		if (!check_sep(token))
			return (false);
		else if (!check_word(token))
			return (false);
		*token_lst = (*token_lst)->next;
	}
	*token_lst = token;
	return (true);
}
