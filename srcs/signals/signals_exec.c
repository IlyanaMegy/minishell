/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:59:07 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/06 10:06:36 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_signal(void)
{
	single_sign_child(false, ADD);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, reset_prompt_handler);
}

void	reset_prompt_handler(int signal)
{
	(void)signal;
	if (single_sign_child(0, GET))
	{
		write(1, "\n", 1);
		single_sign_child(false, ADD);
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit: 3\n", 1);
}

void	heredoc_handler(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	g_sig_exit = 1;
}

bool	quit_da_cmd(int fd[2], int *pid)
{
	waitpid(*pid, pid, 0);
	// signal(SIGQUIT, sigquit_handler);
	single_sign_child(false, ADD);
	close(fd[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (true);
	return (false);
}
