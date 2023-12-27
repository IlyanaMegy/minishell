/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:30:18 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/27 23:37:13 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	main(int ac, char **av, char **arg_env)
{
	t_env	env;

	if (ac > 1 && av)
	{
		ft_memset(&g_minishell, 0, sizeof(t_minishell));
		get_env(arg_env);
		while (1)
		{
			g_minishell.line = readline("minishell$ ");
			if (!g_minishell.line)
				break ;
			if (is_builtin(g_minishell.line))
				exec_builtin(av);
		}
	}
	clean_env();
	return (0);
}
