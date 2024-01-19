/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:31:31 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/19 21:52:14 by ltorkia          ###   ########.fr       */
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
		if (!temp->prev || (temp->prev && temp->prev->type == PIPE)
			|| !last_cmd->cmd)
		{
			last_cmd->cmd = ft_strdup(temp->value);
			if (!last_cmd->cmd)
				return (false);
			temp = temp->next;
		}
		else
		{
			if ((last_cmd && !(last_cmd->args)))
			{
				if (!create_args(&temp, last_cmd))
					return (false);
			}
		}
	}
	*token_lst = temp;
	return (true);
}
