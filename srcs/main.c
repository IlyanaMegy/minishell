/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:30:18 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/12 18:26:37 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// *	LEXER + PARSING -> true = success / false = error
static bool tokenize_and_parse(t_data *data)
{
	if (data->user_input[0])
		add_history(data->user_input);
	else
		return (false);
	// ?	Tokenize the user_input and store it in data->token
	if (!tokenize_input(data, data->user_input))
		return (false);
	// ?	Parse the token list to extract commands and arguments
	if (!get_commands(data, data->token))
		return (false);
	return (true);
}

int	main(int ac, char **av, char **arg_env)
{
	int		exit_s;
	t_data	data;

	(void)ac;
	(void)av;
	// ?	init data to NULL
	ft_memset(&data, 0, sizeof(t_data));
	// ?	stock environment into the linked list t_env thanks to single_env function
	// TODO	use that single_env function to get, update or clear t_env list
	get_env(arg_env);
	// ?	init of exit status to 0 and save it in single_exit_s function
	// TODO	use that single_exit_s function to get or update exit_s value
	exit_s = single_exit_s(0, ADD);
	while (1)
	{
		// ?	stocking the freshly entered input into data.user_input and verify parsing
		data.user_input = readline(PROMPT);
		if (!data.user_input)
			ft_exit(&data);
		if (tokenize_and_parse(&data))
		{
			// *	DEBUG : Print the current command
			print_cmd(data.cmd);
			executie(&data, false);
		}
		free_data(&data);
	}
	clean_program(&data);
	return (single_exit_s(0, 0));
}
