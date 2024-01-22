/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:22 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/22 12:19:22 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Extract commands from a sequence of tokens.
 * @param data Pointer to t_data structure.
 * @param token Pointer to the first token in the sequence.
 */
bool	get_commands(t_data *data, t_token *token)
{
	t_token	*temp_tkn;
	t_cmd	*new_cmd;

	temp_tkn = token;
	while (temp_tkn)
	{
		if (!temp_tkn->prev || temp_tkn->type == PIPE
			|| ((temp_tkn->type > PIPE) && (!temp_tkn->prev)))
		{
			new_cmd = lst_new_cmd();
			if (!new_cmd)
				return (false);
			lst_add_back_cmd(&data->cmd, new_cmd);
			if (temp_tkn->type == PIPE)
				temp_tkn = temp_tkn->next;
		}
		if ((!temp_tkn->prev && temp_tkn->type == WORD)
			|| (temp_tkn->prev && temp_tkn->type == WORD
				&& (temp_tkn->prev->type <= PIPE)))
		{
			if (!handle_word(&data->cmd, &temp_tkn))
				return (false);
		}
		else if (temp_tkn->type > PIPE)
		{
			if (!handle_redir(&data->cmd, &temp_tkn, temp_tkn->type))
				return (false);
		}
		else
			break ;
	}
	if (!set_cmd_without_args(data))
		return (false);
	return (true);
}
