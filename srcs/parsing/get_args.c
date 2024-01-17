/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:31:31 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/17 17:26:28 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	set_cmd_without_args(t_data *data)
{
	t_cmd	*cmd;

	if (!data || !data->cmd)
		return (false);
	cmd = data->cmd;
	while (cmd && cmd->cmd)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			if (!cmd->args)
				return (false);
			cmd->args[0] = ft_strdup(cmd->cmd);
			if (!cmd->args[0])
				return (false);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	return (true);
}

int	count_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD))
	{
		if (temp->next && temp->next->type == TRUNC)
			temp = temp->next;
		i++;
		temp = temp->next;
	}
	return (i);
}

bool	args_default(t_token **token_node, t_cmd **last_cmd, int *index)
{
	while (*token_node && ((*token_node)->type == WORD))
	{
		(*last_cmd)->args[*index] = ft_strdup((*token_node)->value);
		if (!(*last_cmd)->args[*index])
			return (false);
		if ((*token_node)->next && (*token_node)->next->type == TRUNC)
		{
			*token_node = (*token_node)->next;
			if (!handle_input_trunc(last_cmd, token_node, TRUNC))
				return (false);
		}
		else
			*token_node = (*token_node)->next;
		(*index)++;
	}
	return (true);
}

bool	create_args(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		n_args;
	t_token	*temp;

	temp = *token_node;
	n_args = count_args(temp);
	last_cmd->args = malloc(sizeof(char *) * (n_args + 2));
	if (!last_cmd->args)
		return (false);
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->cmd);
	if (!last_cmd->args[i])
		return (false);
	i++;
	if (!args_default(&temp, &last_cmd, &i))
		return (false);
	last_cmd->args[i] = NULL;
	*token_node = temp;
	return (true);
}
