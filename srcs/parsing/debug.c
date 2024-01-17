/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:34:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/17 14:06:05 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	int i = 1;
	while (cmd)
	{
		ft_printf("Commande %d: %s\n", i, cmd->cmd);
		int k = 1;
		while (cmd->io_list)
		{
			ft_printf("- input path %d = %s\n", k, cmd->io_list->path);
			ft_printf("- input type %d = %d\n\n", k, cmd->io_list->type);
			k++;
			cmd->io_list = cmd->io_list->next;
		}
		// if (cmd->io_list)
		// {
		// 	ft_printf("- input path %d = %s\n", k, cmd->io_list->path);
		// 	ft_printf("- input type %d = %d\n\n", k, cmd->io_list->type);
		// }
		int j = 0;
		while (cmd->args[j])
		{
			ft_printf("- arg %d = %s\n", j, cmd->args[j]);
			j++;
		}
		ft_printf("\n");
		i++;
		cmd = cmd->next;
	}
	// exit (0);
}

void	print_token(t_token *token)
{
	int	i = 0;
	ft_printf("\n");
	while (token)
	{
		ft_printf("- token %d = %s -> type = %d\n", i, token->value, token->type);
		i++;
		token = token->next;
	}
	ft_printf("\n");
}
