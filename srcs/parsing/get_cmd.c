/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:22 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/15 18:52:34 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	set_cmd_without_args(t_data *data)
{
	t_cmd	*cmd_head;

	if (!data || !data->cmd)
		return (false);
	cmd_head = data->cmd;
	while (cmd_head && cmd_head->cmd)
	{
		if (!cmd_head->args)
		{
			dprintf(2, "set_cmd_without_args\n");
			cmd_head->args = malloc(sizeof(char *) * 2);
			if (!cmd_head->args)
				return (false);
			cmd_head->args[0] = ft_strdup(cmd_head->cmd);
			// if (cmd_head->cmd)
			// 	cmd_head->args[0] = ft_strdup(cmd_head->cmd);
			// else
			// 	cmd_head->args[0] = NULL;
			if (!cmd_head->args[0])
				return (false);
			cmd_head->args[1] = NULL;
			dprintf(2, "arg[0]: %s\n", cmd_head->args[0]);
		}
		cmd_head = cmd_head->next;
	}
	return (true);
}

static bool	set_new_cmd(t_data *data, t_token **token_lst)
{
	t_cmd	*new_cmd;

	if (!(*token_lst)->prev || (*token_lst)->type == PIPE)
	{
		dprintf(2, "set_new_cmd\n");
		new_cmd = lst_new_cmd();
		if (!new_cmd)
			return (false);
		lst_add_back_cmd(&data->cmd, new_cmd);
		if ((*token_lst)->type == PIPE)
			(*token_lst) = (*token_lst)->next;
	}
	return (true);
}

/**
 * @brief Extract commands from a sequence of tokens.
 * @param data Pointer to t_data structure.
 * @param token Pointer to the first token in the sequence.
 */
bool	set_commands(t_data *data, t_token **token_lst)
{
	t_token	*head;

	head = *token_lst;
	while (head)
	{
		dprintf(2, "On est dans la boucle de creation cmd + args\n");
		if (!set_new_cmd(data, &head))
			return (false);
		if ((!head->prev && head->type == WORD)
			|| (head->prev && head->type == WORD
				&& (head->prev->type <= PIPE)))
		{
			dprintf(2, "On gere le mot\n");
			if (!handle_word(&data->cmd, &head))
				return (false);
		}
		else if (head->type > PIPE)
		{
			dprintf(2, "On gere la redir\n");
			if (!handle_redir(&data->cmd, &head, head->type))
				return (false);
		}
		else
			break ;
	}
	dprintf(2, "On quitte la boucle de creation cmd + args\n");
	if (!set_cmd_without_args(data))
		return (false);
	dprintf(2, "On quitte la fonction de creation cmd + args\n");
	return (true);
}
