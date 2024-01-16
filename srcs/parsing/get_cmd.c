/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:22 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/16 12:06:36 by ltorkia          ###   ########.fr       */
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
		// If at the beginning of the token sequence, add a new empty command
		if (temp_tkn == token || temp_tkn->type == PIPE)
		{
			new_cmd = lst_new_cmd();
			if (!new_cmd)
				return (false);
			lst_add_back_cmd(&data->cmd, new_cmd);
			if (temp_tkn->type == PIPE)
				temp_tkn = temp_tkn->next;
		}
		// if the token is a WORD or VAR (command or argument), parse it
		if (temp_tkn->type == WORD)
		{
			if (!handle_word(&data->cmd, &temp_tkn))
				return (false);
		}
		// if the token is INPUT <
		else if (temp_tkn->type == INPUT)
		{
			if (!handle_input(&data->cmd, &temp_tkn))
				return (false);
		}
		else
			break ;
	}
	// Set commands with no arguments
	if (!set_cmd_without_args(data))
		return (false);
	return (true);
}
