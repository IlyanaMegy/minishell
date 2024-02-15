/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:22 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/15 22:19:20 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	set_cmd_without_args(t_data *data)
{
	t_cmd	*cmd_head;

	if (!data || !data->cmd)
		return (false);
	cmd_head = data->cmd;
	while (cmd_head)
	{
		if (cmd_head->cmd && !cmd_head->args)
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

static bool	set_new_cmd(t_data *data, t_token **token_lst)
{
	t_cmd	*new_cmd;

	if (!(*token_lst)->prev || (*token_lst)->type == PIPE)
	{
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
		if (!set_new_cmd(data, &head))
			return (false);
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
