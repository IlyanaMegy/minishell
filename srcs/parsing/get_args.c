/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:31:31 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/25 21:10:48 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	set_cmd_without_args(t_data *data)
{
	t_cmd	*cmd_head;

	if (!data || !data->cmd)
		return (false);
	cmd_head = data->cmd;
	while (cmd_head && cmd_head->cmd)
	{
		if (!cmd_head->args)
		{
			cmd_head->args = malloc(sizeof * cmd_head->args * 2);
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

int	count_args(t_token *token)
{
	int	i;

	i = 0;
	while (token && (token->type == WORD))
	{
		i++;
		token = token->next;
	}
	return (i);
}

bool	args_default(t_token **token_lst, t_cmd *last_cmd, int *index)
{
	while (*token_lst && ((*token_lst)->type == WORD))
	{
		last_cmd->args[*index] = ft_strdup((*token_lst)->value);
		if (!last_cmd->args[*index])
			return (false);
		*token_lst = (*token_lst)->next;
		(*index)++;
	}
	return (true);
}

bool	create_args(t_token **token_lst, t_cmd *last_cmd)
{
	int		i;
	int		n_args;
	t_token	*head;

	head = *token_lst;
	n_args = count_args(head);
	last_cmd->args = malloc(sizeof(char *) * (n_args + 2));
	if (!last_cmd->args)
		return (single_exit_s(1, ADD), false);
	i = 0;
	last_cmd->args[i] = ft_strdup(last_cmd->cmd);
	if (!last_cmd->args[i])
		return (false);
	i++;
	if (!args_default(&head, last_cmd, &i))
		return (false);
	last_cmd->args[i] = NULL;
	*token_lst = head;
	return (true);
}
