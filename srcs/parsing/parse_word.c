/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:31:31 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/07 23:57:44 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD))
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int create_args(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		n_args;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	n_args = count_args(temp);
	last_cmd->args = malloc(sizeof(char *) * (n_args + 2));
	if (!last_cmd->args)
		return (1);
	temp = *token_node;
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->cmd);
	i++;
	while (temp->type == WORD)
	{
		last_cmd->args[i] = ft_strdup(temp->value);
		i++;
		temp = temp->next;
	}
	last_cmd->args[i] = NULL;
	*token_node = temp;
	return (0);
}

/**
 * @brief Parse a sequence of tokens and extract commands and their arguments.
 * @param cmd Pointer to the pointer of t_cmd structure.
 * @param token_lst Pointer to the pointer of t_token structure (list of tokens).
 */
void	parse_word(t_cmd **cmd, t_token **token_lst)
{
	t_token		*temp;
	t_cmd		*last_cmd;

	temp = *token_lst;
	while (temp->type == WORD)
	{
		last_cmd = lst_last_cmd(*cmd);
		// Check if the token is at the beginning of a command
		if (!temp->prev || (temp->prev && temp->prev->type == PIPE)
			|| !last_cmd->cmd)
		{
			// If so, copy the word as the command
			last_cmd->cmd = ft_strdup(temp->value);
			temp = temp->next;
		}
		else
			// If not, fill the arguments of the current command
			if (last_cmd && !(last_cmd->args))
				create_args(&temp, last_cmd);
	}
	*token_lst = temp;
}