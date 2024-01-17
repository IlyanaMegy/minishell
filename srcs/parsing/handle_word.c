/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:31:31 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/17 13:54:11 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Parse a sequence of tokens and extract commands and their arguments.
 * @param cmd Pointer to the pointer of t_cmd structure.
 * @param token_lst Pointer to the pointer of t_token structure (list of tokens).
 */
bool	handle_word(t_cmd **cmd, t_token **token_lst)
{
	t_token		*temp;
	t_cmd		*last_cmd;

	temp = *token_lst;
	while (temp && temp->type == WORD)
	{
		last_cmd = lst_last_cmd(*cmd);
		// Check if the token is at the beginning of a command
		if (!temp->prev || (temp->prev && temp->prev->type == PIPE)
			|| !last_cmd->cmd)
		{
			// If so, and it's a WORD, copy the word as the command
			last_cmd->cmd = ft_strdup(temp->value);
			if (!last_cmd->cmd)
				return (false);
			temp = temp->next;
		}
		else
		{
			// If not, fill the arguments of the current command
			if ((last_cmd && !(last_cmd->args))
				|| (last_cmd->args && temp->prev->type == TRUNC))
			{
				if (!create_args(&temp, last_cmd))
					return (false);
			}
		}
	}
	*token_lst = temp;
	return (true);
}
