/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:31:31 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/26 12:36:23 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_args(t_token *token)
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

static char	**new_args_tab(char **tab, int len,
	t_token **token_lst, t_cmd *last_cmd)
{
	int	i;

	i = 0;
	while (last_cmd->args[i])
	{
		tab[i] = ft_strdup(last_cmd->args[i]);
		if (!tab[i])
			return (free_tab(tab), NULL);
		i++;
	}
	while (i < len)
	{
		tab[i] = ft_strdup((*token_lst)->value);
		if (!tab[i])
			return (free_tab(tab), NULL);
		*token_lst = (*token_lst)->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static bool	args_default(t_token **token_lst, t_cmd *last_cmd, int *index)
{
	while (*token_lst && ((*token_lst)->type == WORD))
	{
		last_cmd->args[*index] = ft_strdup((*token_lst)->value);
		if (!last_cmd->args[*index])
			return (free_tab(last_cmd->args), false);
		*token_lst = (*token_lst)->next;
		(*index)++;
	}
	return (true);
}

bool	add_more_args(t_token **token_lst, t_cmd *last_cmd)
{
	int		i;
	int		len;
	char	**new_args;
	t_token	*head;

	head = *token_lst;
	i = 0;
	while (last_cmd->args[i])
		i++;
	len = i + count_args(head);
	new_args = malloc(sizeof(char *) * (len + 1));
	if (!new_args)
		return (false);
	new_args = new_args_tab(new_args, len, &head, last_cmd);
	if (!new_args)
		return (false);
	free_tab(last_cmd->args);
	last_cmd->args = new_args;
	*token_lst = head;
	return (true);
}

bool	set_args(t_token **token_lst, t_cmd *last_cmd)
{
	int		i;
	int		n_args;
	t_token	*head;

	head = *token_lst;
	n_args = count_args(head);
	last_cmd->args = malloc(sizeof(char *) * (n_args + 2));
	if (!last_cmd->args)
		return (false);
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
