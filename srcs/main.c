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

#include "../inc/minishell.h"

int	main(int ac, char **av, char **arg_env)
{
	char	*cmd_line;

	(void)ac;
	(void)av;
	get_env(arg_env);
	while (1)
	{
		cmd_line = readline("minishell$ ");
		if (!cmd_line || !ft_strcmp(cmd_line, "exit"))
			break ;
		ft_printf("you said : \"%s\"\n", cmd_line);
		free(cmd_line);
		// if (is_builtin(g_minishell.line))
		// 	exec_builtin(av);
	}
	// display_export();
	// ft_printf("\n\n");
	// ft_env();
	clean_env(single_env(NULL, 0));
	return (0);
}
