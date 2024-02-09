/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:59:07 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/09 11:02:49 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_signal(void)
{
	g_sig_exit = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, reset_prompt_handler);
}

void	reset_prompt_handler(int signal)
{
	(void)signal;
	single_exit_s(130, ADD);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
