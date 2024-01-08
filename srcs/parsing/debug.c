/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:34:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/07 22:27:48 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	ft_printf("Commande actuelle: %s\n", cmd->cmd);
	int j = 1;
	while (cmd->args[j])
	{
		ft_printf("- arg %d = %s\n", j, cmd->args[j]);
		j++;
	}
	ft_printf("\n");
}

void	print_token(t_token *token)
{
	int	i = 0;
	ft_printf("\n");
	while (token)
	{
		ft_printf("- token %d = %s | type = %d\n", i, token->value, token->type);
		i++;
		token = token->next;
	}
	ft_printf("\n");
}