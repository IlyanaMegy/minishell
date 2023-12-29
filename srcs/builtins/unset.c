/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:07 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/27 21:22:15 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   remove a variable from the environment ?
 * @param  var_name: variable name
 * @retval None
*/
void	remove_var_from_env(char *var_name)
{
	t_env	*e;

	e = single_env(NULL, GET);
	while (e)
	{
		if (!ft_strcmp(e->name, var_name))
		{
			if (e->prev != NULL)
				e->prev->next = e->next;
			if (e->next != NULL)
				e->next->prev = e->prev;
			free(e->content);
			free(e->name);
			free(e);
			return ;
		}
		e = e->next;
	}
}

/**
 * @note   unset a variable from the environment
 * @param  args: variables to unset from the environment
 * @retval exit status
*/
int	ft_unset(char **args)
{
	int	i;
	int	exit_status;

	if (!args[1])
		return (0);
	i = 1;
	exit_status = 0;
	while (args[i])
	{
		if (!check_var_name(args[i], 0))
		{
			err_handler(ERR_UNSET, args[i]);
			exit_status = 1;
		}
		else if (var_is_in_env(args[i]))
			remove_var_from_env(args[i]);
		i++;
	}
	return (exit_status);
}
