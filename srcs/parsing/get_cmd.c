/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:22 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/26 12:19:57 by ltorkia          ###   ########.fr       */
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
			cmd_head->args = malloc(sizeof(char *) * 2);
			if (!cmd_head->args)
				return (false);
			cmd_head->args[0] = ft_strdup(cmd_head->cmd);
			if (!cmd_head->args[0])
				return (false);
			cmd_head->args[1] = NULL;
		}
		cmd_head = cmd_head->next;
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
	t_cmd	*new_cmd;

	head = *token_lst;
	while (head)
	{
		if (!head->prev || head->type == PIPE
			|| (head->type > PIPE && !head->prev))
		{
			new_cmd = lst_new_cmd();
			if (!new_cmd)
				return (false);
			lst_add_back_cmd(&data->cmd, new_cmd);
			if (head->type == PIPE)
				head = head->next;
		}
		if ((!head->prev && head->type == WORD)
			|| (head->prev && head->type == WORD
				&& (head->prev->type <= PIPE)))
		{
			if (!handle_word(&data->cmd, &head))
				return (false);
		}
		else if (head->type > PIPE)
		{
			if (!handle_redir(&data->cmd, &head, head->type))
				return (false);
		}
		else
			break ;
	}
	if (!set_cmd_without_args(data))
		return (false);
	return (true);
}
