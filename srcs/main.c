/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:30:18 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/07 23:29:15 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		ft_printf("%s\n", tab[i]);
}

/* token + parse input in structure for execution
*   true = success, false = error
*/
static bool	tokenize_and_parse(t_data *data)
{
	// Check if user_input is not NULL and add it to history
	if (data->user_input)
		add_history(data->user_input);
	else
		return (false);
	// Tokenize the user_input and store it in data->token
	if (!tokenize_input(data, data->user_input))
		return (false);
	// Check if the token list is empty (END_STR) and return false if it is
	if (data->token->type == END_STR)
		return (false);
	// Parse the token list to extract commands and arguments
	get_commands(data, data->token);
	// ------------------------ DEBUG ------------------------ //
	// Print the current token list
	print_token(data->token);
	// ---------------------- FIN DEBUG ---------------------- //
	return (true);
}

int	main(int ac, char **av, char **arg_env)
{
	int		exit_s;
	char	**env_tab;
	t_data	data;

	(void)ac;
	(void)av;
	// Init data to NULL
	ft_memset(&data, 0, sizeof(t_data));
	// ?	stock environment into the linked list t_env thanks to single_env function
	// TODO	use that single_env function to get, update or clear t_env list
	get_env(arg_env);
	// ?	init of exit status to 0 and save it in single_exit_s function
	// TODO	use that single_exit_s function to get or update exit_s value
	exit_s = single_exit_s(0, ADD);
	env_tab = env_to_tab(single_env(NULL, GET));
	print_tab(env_tab);
	while (1)
	{
		// ?	stocking the freshly entered input into data.user_input and verify parsing
		data.user_input = readline(PROMPT);
		if (tokenize_and_parse(&data))
		{
			// DEBUG : Print the current command
			print_cmd(data.cmd);
			// ?	checking if current_cmd->cmd which is the command is a builtin
			// ?	then executing the builtin if so and save exit status
			if (is_builtin(data.cmd->cmd))
				single_exit_s(exec_builtin(data.cmd->args), ADD);
		}
		free_data(&data);
	}
	clean_env(single_env(NULL, 0));
	return (single_exit_s(0, 0));
}
