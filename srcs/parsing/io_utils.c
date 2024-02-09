/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:18 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/06 10:20:59 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	init_io_cmd_node(t_io_cmd *io_node)
{
	io_node->path = NULL;
	io_node->expanded_value = NULL;
	io_node->type = -1;
	io_node->here_doc = 0;
	io_node->next = NULL;
	io_node->prev = NULL;
}

bool	init_io_cmd(t_cmd *cmd)
{
	t_io_cmd	*temp;

	if (!cmd->io_list)
	{
		cmd->io_list = (t_io_cmd *)malloc(sizeof(t_io_cmd));
		if (!(cmd->io_list))
			return (false);
		init_io_cmd_node(cmd->io_list);
	}
	else
	{
		temp = cmd->io_list;
		while (temp->next)
			temp = temp->next;
		temp->next = (t_io_cmd *)malloc(sizeof(t_io_cmd));
		if (!temp->next)
			return (false);
		init_io_cmd_node(temp->next);
		temp->next->prev = temp;
	}
	return (true);
}

void	lstdelone_io_list(t_io_cmd *io_node, void (*del)(void *))
{
	if (io_node->path)
		(*del)(io_node->path);
	if (io_node->expanded_value)
		free_tab(io_node->expanded_value);
	(*del)(io_node);
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
