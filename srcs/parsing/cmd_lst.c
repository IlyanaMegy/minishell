/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:18 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/08 11:09:56 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool    init_io_cmd(t_cmd **node)
{
    (*node)->io_list = (t_io_cmd *)malloc(sizeof(t_io_cmd));
    (*node)->io_list->next = (t_io_cmd *)malloc(sizeof(t_io_cmd));
    if (!((*node)->io_list) || !((*node)->io_list->next))
        return (false);
    (*node)->io_list->path = NULL;
    (*node)->io_list->type = IO_IN;
    (*node)->io_list->here_doc = 0;
    (*node)->io_list->prev = NULL;
    (*node)->io_list->next->type = IO_OUT;
    (*node)->io_list->next->path = NULL;
    (*node)->io_list->next->here_doc = 0;
    (*node)->io_list->next->prev = (*node)->io_list;
    (*node)->io_list->next->next = NULL;
    return (true);
}

t_cmd    *lst_new_cmd(bool pipe)
{
    t_cmd    *node;

    node = (t_cmd *)malloc(sizeof(t_cmd));
    if (!(node))
        return (NULL);
    if (!init_io_cmd(&node))
        return (NULL);
    (node)->cmd = NULL;
    (node)->args = NULL;
    (node)->pipe_out = pipe;
    (node)->prev = NULL;
    (node)->next = NULL;
    return (node);
}

void	lst_add_back_cmd(t_cmd **alst, t_cmd *node)
{
	t_cmd	*start;

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

t_cmd	*lst_last_cmd(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	lstdelone_cmd(t_cmd *lst, void (*del)(void *))
{
	if (lst->cmd)
		(*del)(lst->cmd);
	if (lst->args)
		free_tab(lst->args);
	(*del)(lst);
}

void	lstclear_cmd(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*temp;

	temp = NULL;
	while (*lst)
	{
		temp = (*lst)->next;
		lstdelone_cmd(*lst, del);
		*lst = temp;
	}
}
