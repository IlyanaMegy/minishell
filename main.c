/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:30:18 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/13 16:30:19 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	main(int ac, char **av, char **arg_env)
{
	t_env	env;

	if (ac > 1)
		ft_printf("argv = %s\n", av[0]);
	get_env(arg_env, &env);
	ft_env(&env);
	ft_printf("\n\n\n");
	ft_export(&env);
	return (0);
}
