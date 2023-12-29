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
	char **cmd;

	(void)ac;
	(void)av;
	get_env(arg_env);
	while (1)
	{
		cmd_line = readline("minishell$ ");
		if (!cmd_line || !ft_strcmp(cmd_line, "exit"))
			break ;
		cmd = ft_split(cmd_line, ' ');
		if (is_builtin(cmd[0]))
			exec_builtin(cmd);
		free(cmd_line);
		free_tab(cmd);
	}
	clean_env(single_env(NULL, 0));
	return (0);
}
