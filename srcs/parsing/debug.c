/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:34:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/20 13:24:35 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_iolist(t_cmd *cmd)
{
	int			k;
	t_io_cmd	*temp_io_list;

	k = 1;
	temp_io_list = cmd->io_list;
	while (cmd && temp_io_list)
	{
		dprintf(2, "- path %d = %s\n", k, temp_io_list->path);
		dprintf(2, "- type %d = %d\n\n", k, temp_io_list->type);
		k++;
		temp_io_list = temp_io_list->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int			i;
	int			j;
	t_cmd		*temp;

	i = 1;
	temp = cmd;
	while (temp)
	{
		dprintf(2, "\nCommande %d: %s\n", i++, temp->cmd);
		print_iolist(temp);
		j = 0;
		while (temp && temp->args && temp->args[j])
		{
			dprintf(2, "- arg %d = %s\n", j, temp->args[j]);
			j++;
		}
		temp = temp->next;
	}
}

void	print_token(t_token *token)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = token;
	dprintf(2, "\n");
	while (temp)
	{
		dprintf(2, "- token %d = %s -> type = %d -> len: %ld\n",
			i, temp->value, temp->type, ft_strlen(temp->value));
		i++;
		temp = temp->next;
	}
	dprintf(2, "\n");
}

void	print_expanded_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		dprintf(2, "- expanded arg %d = %s\n", i, args[i]);
		i++;
	}
}
