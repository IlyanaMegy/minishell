/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:59:07 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/09 11:09:12 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	sig_child(int signal)
{
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit\n", 1);
	else if (signal == SIGINT)
		write(1, "\n", 1);
}

void	set_sig_child(void)
{
	signal(SIGINT, sig_child);
	signal(SIGQUIT, sig_child);
	signal(SIGPIPE, sig_child);
}

void	heredoc_handler(int signal)
{
	(void)signal;
	g_sig_exit = 1;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	catch_sigint_exit(t_data *data)
{
	if (g_sig_exit)
	{
		g_sig_exit = 0;
		clean_program(data);
		exit(2);
	}
}

bool	quit_da_cmd(int fd[2], int *pid)
{
	waitpid(*pid, pid, 0);
	close(fd[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (single_exit_s(130, ADD), true);
	return (false);
}
