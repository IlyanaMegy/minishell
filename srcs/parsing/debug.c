/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:34:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/15 22:39:30 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_expanded_args(char **args)
{
	int i = 0;
	while (args && args[i])
	{
		dprintf(2, "- expanded arg %d = %s\n", i, args[i]);
		i++;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int i = 1;
	t_cmd	*temp;
	t_io_cmd *temp_io_list;

	temp = cmd;
	while (temp)
	{
		dprintf(2, "\nCommande %d: %s\n", i++, temp->cmd);
		int k = 1;
		temp_io_list = temp->io_list;
		while (temp_io_list)
		{
			dprintf(2, "- path %d = %s\n", k, temp_io_list->path);
			dprintf(2, "- type %d = %d\n\n", k, temp_io_list->type);
			k++;
			temp_io_list = temp_io_list->next;
		}
		int j = 0;
		while (temp->args && temp->args[j])
		{
			dprintf(2, "- arg %d = %s\n", j, temp->args[j]);
			j++;
		}
		temp = temp->next;
	}
}

void	print_token(t_token *token)
{
	int	i = 0;
	t_token *temp = token;
	dprintf(2, "\n");
	while (temp)
	{
		dprintf(2, "- token %d = %s -> type = %d -> len: %ld\n", i, temp->value, temp->type, ft_strlen(temp->value));
		i++;
		temp = temp->next;
	}
	dprintf(2, "\n");
}
