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
	if (ac > 0 && av)
	{
		// ft_memset(&g_minishell, 0, sizeof(t_minishell));
		get_env(arg_env);
		ft_env();
		// display_export();
		ft_printf("\n\n______________________________________\n\n");

		ft_unset(av);
		// ft_env();
		display_export();
		// while (1)
		// {
		// 	t_minishell.line = readline("minishell$ ");
		// 	if (!g_minishell.line)
		// 		break ;
		// 	if (is_builtin(g_minishell.line))
		// 		exec_builtin(av);
		// }
		single_env(NULL, RM);
	}
	
	return (0);
}
