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
	int exit_s;

	(void)ac;
	(void)av;
	// ?	stock environment into the linked list t_env thanks to single_env function
	// TODO	use that single_env function to get, update or clear t_env list
	get_env(arg_env);

	// ?	init of exit status to 0 and save it in single_exit_s function
	// TODO	use that single_exit_s function to get or update exit_s value
	exit_s = single_exit_s(0, ADD);
	while (1)
	{
		// ?	stocking the freshly entered input into cmd_line and verify it's not null
		cmd_line = readline("minishell$ ");
		if (!cmd_line)
			break ;

		// ?	spliting cmd_line each ' ' and stocking it into char** cmd
		cmd = ft_split(cmd_line, ' ');
		free(cmd_line);

		// ?	checking if cmd[0] which is the command is a builtin
		// ?	then executing the builtin if so and save exit status
		if (is_builtin(cmd[0]))
			single_exit_s(exec_builtin(cmd), ADD);

		free_tab(cmd);
	}
	clean_env(single_env(NULL, 0));
	return (single_exit_s(0, 0));
}
