/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_interact.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:50:10 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/15 21:42:00 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_minishell(char *s)
{
	if (ft_strcmp(s, "./minishell") == 0)
		return (true);
	return (false);
}

static int	n_minishell(t_token *token)
{
	int		count;

	count = 0;
	while (token)
	{
		if (is_minishell(token->value))
			count++;
		token = token->next;
	}
	return (count);
}

bool	check_interact(t_token *token)
{
	int		count;

	count = n_minishell(token);
	if (is_minishell(token->value) && count > 1)
		return (false);
	return (true);
}
