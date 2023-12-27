/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:30:18 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/27 18:01:39 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

t_minishell	g_minishell;

int	main(int ac, char **av, char **arg_env)
{
	t_env	env;

	if (ac > 1 && av)
	{
		get_env(arg_env, &env);
		while (1)
		{
			g_minishell.line = readline("minishell$ ");
			if (!g_minishell.line)
				break ;
			ft_printf("you said : %s\n", g_minishell.line);
		}
	}
	clean_env(&env);
	return (0);
}
