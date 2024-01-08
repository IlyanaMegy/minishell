/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:50:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/07 20:34:58 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*lst_new_token(char *value, int type, int quote_status)
{
	t_token	*node;

	node = malloc(sizeof(t_token) * 1);
	if (!(node))
		return (NULL);
	node->value = value;
	node->type = type;
	node->quote_status = quote_status;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	lst_add_back_token(t_token **alst, t_token *node)
{
	t_token	*start;

	start = *alst;
	if (!start)
	{
		*alst = node;
		return ;
	}
	if (alst && *alst && node)
	{
		while (start->next)
			start = start->next;
		start->next = node;
		node->prev = start;
	}
}

void	lstdelone_token(t_token *lst, void (*del)(void *))
{
	if (del && lst && lst->value)
	{
		(*del)(lst->value);
		lst->value = NULL;
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	free_ptr(lst);
}

void	lstclear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*lst)
	{
		tmp = (*lst)->next;
		lstdelone_token(*lst, del);
		*lst = tmp;
	}
}
