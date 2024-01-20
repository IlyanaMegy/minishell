#include "../../inc/minishell.h"

// static void	heredoc_sigint_handler(t_data *data, int signum)
// {
// 	(void)signum;
// 	clean_program(data);
// 	exit(SIGINT);
// }

// static bool	quit_da_cmd(t_data *data, int fd[2], int *pid)
// {
// 	waitpid(*pid, pid, 0);
// 	signal(SIGQUIT, ft_sigquit_handler);
// 	data->signint_child = false;
// 	close(fd[1]);
// 	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
// 		return (true);
// 	return (false);
// }
