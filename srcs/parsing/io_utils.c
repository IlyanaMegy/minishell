/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:18 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/17 15:54:24 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	create_new_io_list(t_cmd **cmd, t_io_cmd **temp)
{
	(*cmd)->io_list = (t_io_cmd *)malloc(sizeof(t_io_cmd));
	if (!((*cmd)->io_list))
		return (false);
	(*temp) = (*cmd)->io_list;
	(*temp)->prev = NULL;
	return (true);
}

static bool	add_io_list_next(t_cmd **cmd, t_io_cmd **temp)
{
	(*temp) = (*cmd)->io_list;
	while ((*temp)->next)
		(*temp) = (*temp)->next;
	(*temp)->next = (t_io_cmd *)malloc(sizeof(t_io_cmd));
	if (!(*temp)->next)
		return (false);
	(*temp)->next->prev = (*temp);
	(*temp) = (*temp)->next;
	return (true);
}

bool	init_io_cmd(t_cmd **cmd)
{
	t_io_cmd	*temp;

	if (!(*cmd)->io_list)
	{
		if (!create_new_io_list(cmd, &temp))
			return (false);
	}
	else
	{
		if (!add_io_list_next(cmd, &temp))
			return (false);
	}
	temp->path = NULL;
	temp->type = -1;
	temp->here_doc = 0;
	temp->next = NULL;
	return (true);
}

void	lstdelone_io_list(t_io_cmd *io_list, void (*del)(void *))
{
	if (io_list->path)
		(*del)(io_list->path);
	(*del)(io_list);
}

void	lstclear_io_list(t_io_cmd **io_list, void (*del)(void *))
{
	t_io_cmd	*temp;

	temp = NULL;
	while (*io_list)
	{
		temp = (*io_list)->next;
		lstdelone_io_list(*io_list, del);
		*io_list = temp;
	}
}
