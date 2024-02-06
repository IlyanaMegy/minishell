/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:30:18 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/06 09:58:04 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_exit;

static bool	tokenize_and_parse(t_data *data)
{
	if (data->user_input[0])
		add_history(data->user_input);
	else
		return (false);
	if (!tokenize_input(data, data->user_input))
		return (false);
	if (!set_commands(data, &data->token))
		return (single_exit_s(1, ADD), false);
	return (true);
}

static void	non_interactive_mode(t_data *data)
{
	data->user_input = get_next_line(data->stdin);
	if (!data->user_input)
		(clean_program(data), ft_putstr_fd("exit\n", 1), exit(1));
	while (data->user_input)
	{
		if (tokenize_and_parse(data))
		{
			init_cmdlst(data, data->cmd);
			executie(data, data->cmd, false);
		}
		free_data(data);
		data->user_input = get_next_line(data->stdin);
	}
}

static void	init_data_and_env(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	g_sig_exit = 0;
	set_signal();
	data->stdin = dup(0);
	data->stdout = dup(1);
}

int	main(int ac, char **av, char **arg_env)
{
	t_data	data;

	(void)ac;
	(void)av;
	// ?	init data to NULL
	init_data_and_env(&data);
	// ?	stock environment into the linked list t_env thanks to single_env function
	// TODO	use that single_env function to get, update or clear t_env list
	get_env(arg_env);
	// ?	init of exit status to 0 and save it in single_exit_s function
	// TODO	use that single_exit_s function to get or update exit_s value
	single_exit_s(0, ADD);
	if (isatty(data.stdin))
	{
		while (1)
		{
			// ?	stocking the freshly entered input into data.user_input and verify parsing
			data.user_input = readline(PROMPT);
			if (!data.user_input)
				(clean_program(&data), ft_putstr_fd("exit\n", 1), exit(1));
			if (tokenize_and_parse(&data))
			{
				if (init_cmdlst(&data, data.cmd))
					executie(&data, data.cmd, false);
			}
			free_data(&data);
		}
	}
	else
		non_interactive_mode(&data);
	clean_program(&data);
	return (single_exit_s(0, GET));
}
