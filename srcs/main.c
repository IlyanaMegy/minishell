/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:30:18 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/23 14:38:30 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			g_sig_exit;

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
	data->user_input = get_next_line(STDIN_FILENO);
	if (!data->user_input)
		(clean_program(data), exit(single_exit_s(0, GET)));
	while (data->user_input)
	{
		if (tokenize_and_parse(data))
		{
			if (init_cmdlst(data, data->cmd))
				executie(data, data->cmd, false);
		}
		free_data(data);
		data->user_input = get_next_line(STDIN_FILENO);
	}
	clean_program(data);
	exit(single_exit_s(0, GET));
}

static void	init_data_env(t_data *data, char **arg_env)
{
	ft_memset(data, 0, sizeof(t_data));
	g_sig_exit = 0;
	get_env(arg_env);
	single_exit_s(0, ADD);
	if (!isatty(STDIN_FILENO))
		non_interactive_mode(data);
}

int	main(int ac, char **av, char **arg_env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data_env(&data, arg_env);
	while (1)
	{
		data.stdin = dup(0);
		data.stdout = dup(1);
		set_signal();
		data.user_input = readline(PROMPT);
		if (!data.user_input)
			(clean_program(&data), ft_putstr_fd("exit\n", 1),
				exit(single_exit_s(0, GET)));
		if (tokenize_and_parse(&data))
		{
			if (init_cmdlst(&data, data.cmd))
				executie(&data, data.cmd, false);
		}
		free_data(&data);
	}
	clean_program(&data);
	return (single_exit_s(0, GET));
}
