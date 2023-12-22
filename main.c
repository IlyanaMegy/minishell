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
	char *unset_me[3];

	unset_me[0] = "hello";
	unset_me[1] = "toto";
	if (ac > 1)
		ft_printf("argv = %s\n", av[0]);
	if (get_env(arg_env, &env))
		return (1);
	ft_env(&env);
	ft_printf("\n\n----------------------------------\n\n");
	++(av);
	ft_cd(&env, av);
	ft_env(&env);
	clean_env(&env);
	return (0);
}
