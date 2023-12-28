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
	// t_envlst envlst;
	if (ac > 0 && av)
	{
		// ft_memset(&envlst, 0, sizeof(t_envlst));
		// envlst.first = single_env(NULL, 0);
		get_env(arg_env);
		ft_env();


		ft_printf("\n\n______________________________________\n\n");

		// ft_unset(av);
		// ft_env();
		display_export();

		ft_printf("\n\n______________________________________\n\n");

		// ft_unset(av);
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
		clean_env(single_env(NULL, 0));
	}
	
	return (0);
}
