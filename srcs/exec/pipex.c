#include "../../inc/minishell.h"

void	init_values(int fds[6], t_cmd *cmd_lst, t_cmd **c)
{
	*c = cmd_lst;
	fds[5] = 0;
	if (cmd_lst->next)
		fds[5] = 1;
	// fds[4] = -1;
	// here_docs
	fds[2] = STDIN_FILENO;
	fds[3] = STDOUT_FILENO;
}

void	init_pipex(t_cmd *cmd_lst)
{
	t_cmd *c;
	int fds[6];

	init_values(fds, cmd_lst, &c);
	while (c)
	{
		if (c->prev)
		{
			if (fds[4] == -1)
				fds[4] = dup(fds[0]);
			else
				dup2(fds[0], fds[4]);
			if (fds[0] > -1)
				close(fds[0]);
			if (fds[1] > -1)
				close(fds[1]);
		}
		if (c->next)
			pipe(fds);
		// executie();
		c = c->next;
	}
	// close, wait, clear
}
