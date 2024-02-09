/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:31:31 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/06 10:22:03 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Parse a sequence of tokens and extract commands and their arguments.
 * @param cmd Pointer to the pointer of t_cmd structure.
 * @param token_lst Pointer to the pointer of t_token structure (list of tokens).
 */
bool	handle_word(t_cmd **cmd_lst, t_token **token_lst)
{
	t_token		*head_token;
	t_cmd		*last_cmd;

	head_token = *token_lst;
	while (head_token && head_token->type == WORD)
	{
		last_cmd = lst_last_cmd(*cmd_lst);
		if (!head_token->prev
			|| (head_token->prev && head_token->prev->type == PIPE)
			|| !last_cmd->cmd)
		{
			last_cmd->cmd = ft_strdup(head_token->value);
			if (!last_cmd->cmd)
				return (false);
			head_token = head_token->next;
		}
		else if (last_cmd && !(last_cmd->args)
			&& !set_args(&head_token, last_cmd))
			return (false);
		else if (last_cmd && last_cmd->args && last_cmd->io_list
			&& !add_more_args(&head_token, last_cmd))
			return (false);
	}
	*token_lst = head_token;
	return (true);
}
