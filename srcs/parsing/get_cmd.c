/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:08:22 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/07 21:52:23 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	no_arg_cmds(t_data *data)
{
	t_cmd	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd && cmd->cmd)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			cmd->args[0] = ft_strdup(cmd->cmd);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(data->cmd);
}

/**
 * @brief Extract commands from a sequence of tokens.
 * @param data Pointer to t_data structure.
 * @param token Pointer to the first token in the sequence.
 */
void	get_commands(t_data *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	// Check if the sequence of tokens is empty
	if (temp->type == END_STR)
		return ;
	while (temp->next)
	{
		// If at the beginning of the token sequence, add a new empty command
		if (temp == token)
			lst_add_back_cmd(&data->cmd, lst_new_cmd());
		// If the token is a word (command or argument), parse it
		if (temp->type == WORD)
			parse_word(&data->cmd, &temp);
		// If the end of the token sequence is reached, break the loop
		else if (temp->type == END_STR)
			break ;
	}
	// Process commands with no arguments
	no_arg_cmds(data);
}