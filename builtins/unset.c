/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:07 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/13 16:22:10 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(t_env *env, char **args)
{
	int i;
	int exit_status;

	if (!args[1])
		return (0);
	i = 1;
	exit_status = 0;
	while (args[i])
	{
		if (!check_var_name(args[i], 0))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status = 1;
		}
		else if (var_is_in_env(env, args[i]))
		{
			//rm
		}
	}
	return (exit_status);
}