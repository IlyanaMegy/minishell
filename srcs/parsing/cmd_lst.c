/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:18 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/20 13:29:39 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*lst_new_cmd(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->io_list = NULL;
	node->cmd = NULL;
	node->args = NULL;
	node->expanded_args = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	lst_add_back_cmd(t_cmd **cmd_lst, t_cmd *cmd)
{
	t_cmd	*start;

	start = *cmd_lst;
	if (!start)
	{
		*cmd_lst = cmd;
		return ;
	}
	if (cmd_lst && *cmd_lst && cmd)
	{
		while (start->next)
			start = start->next;
		start->next = cmd;
		cmd->prev = start;
	}
}

t_cmd	*lst_last_cmd(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	lstdelone_cmd(t_cmd *cmd, void (*del)(void *))
{
	if (cmd->cmd)
		(*del)(cmd->cmd);
	if (cmd->args)
		free_tab(cmd->args);
	if (cmd->expanded_args)
	{
		free_tab(cmd->expanded_args);
		cmd->path_err.path = NULL;
	}
	if (cmd->io_list)
		lstclear_io_list(&cmd->io_list, del);
	(*del)(cmd);
}

void	lstclear_cmd(t_cmd **cmd_lst, void (*del)(void *))
{
	t_cmd	*temp;

	temp = NULL;
	while (*cmd_lst)
	{
		temp = (*cmd_lst)->next;
		lstdelone_cmd(*cmd_lst, del);
		*cmd_lst = temp;
	}
}
