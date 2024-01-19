/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:34:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/19 21:50:46 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	int i = 1;
	t_cmd	*temp;
	t_io_cmd *temp_io_list;

	temp = cmd;
	while (temp)
	{
		dprintf(2, "Commande %d: %s\n", i++, temp->cmd);
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
		while (temp->args[j])
		{
			dprintf(2, "- arg %d = %s\n", j, temp->args[j]);
			j++;
		}
		dprintf(2, "\n");
		temp = temp->next;
	}
	// exit (0);
}

void	print_token(t_token *token)
{
	int	i = 0;
	t_token *temp = token;
	dprintf(2, "\n");
	while (temp)
	{
		dprintf(2, "- token %d = %s -> type = %d\n", i, temp->value, temp->type);
		i++;
		temp = temp->next;
	}
	dprintf(2, "\n");
}
