/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:50:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/25 21:06:06 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*lst_new_token(char *value, t_token_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token) * 1);
	if (!(node))
		return (NULL);
	node->value = value;
	node->type = type;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	lst_add_front_token(t_token **token_lst, t_token *node)
{
	if (!token_lst || !node)
		return ;
	node->next = *token_lst;
	*token_lst = node;
}

void	lst_add_back_token(t_token **token_lst, t_token *node)
{
	t_token	*start;

	start = *token_lst;
	if (!start)
	{
		*token_lst = node;
		return ;
	}
	if (token_lst && *token_lst && node)
	{
		while (start->next)
			start = start->next;
		start->next = node;
		node->prev = start;
	}
}

void	lstdelone_token(t_token *token, void (*del)(void *))
{
	if (del && token && token->value)
	{
		(*del)(token->value);
		token->value = NULL;
	}
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	free_ptr(token);
}

void	lstclear_token(t_token **token_lst, void (*del)(void *))
{
	t_token	*temp;

	temp = NULL;
	while (*token_lst)
	{
		temp = (*token_lst)->next;
		lstdelone_token(*token_lst, del);
		*token_lst = temp;
	}
}
