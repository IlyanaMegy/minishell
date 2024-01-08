#include "../../inc/minishell.h"

static void	sigint_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// static void	sigquit_handler(int signal)
// {
// 	(void)signal;
// 	ft_putstr_fd("Exit\n", 1);
// }

void	init_signals(void)
{
    // Displays a new prompt on a new line
    // signal(SIGINT, sigint_handler);
    // Ignore SIGQUIT (CTRL -\)
    // signal(SIGQUIT, SIG_IGN);
}