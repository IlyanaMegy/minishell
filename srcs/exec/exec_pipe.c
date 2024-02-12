#include "../../inc/minishell.h"

void	ft_close_all(int fd[4])
{
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

void	ft_dup2(int fdin, int fdout, int close_it)
{
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	if (close_it != -1)
		close(close_it);
}

void	swap_pipes(int fd[4])
{
	dup2(fd[0], fd[2]);
	close(fd[0]);
	close(fd[1]);
}

void	exec_pipe_child(t_data *data, t_cmd *cmd, int *status, int fd[4])
{
	t_path	path;
	char	**env;

	if (!cmd->prev)
	{
		// dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	// ft_dup2(fd[0], fd[1], fd[0]);
	if (!cmd->next)
	{
		dup2(fd[2], STDIN_FILENO);
		close(fd[1]);
		// dup2(fd[1], STDOUT_FILENO);
	}
	// ft_dup2(fd[2], fd[1], fd[1]);
	else if (cmd->next && cmd->prev)
		ft_dup2(fd[2], fd[1], -1);
	ft_close_all(fd);
	if (cmd_is_dot(cmd->expanded_args[0]))
		get_out(data, ENO_MISS_CMD, NULL, status);
	if (cmd_is_dir(cmd->expanded_args[0]))
		get_out(data, ENO_CANT_EXEC, NULL, status);
	env = env_to_tab(single_env(NULL, GET));
	if (!env)
		get_out(data, ENO_GENERAL, NULL, status);
	if (check_redir(cmd) != ENO_SUCCESS)
		get_out(data, ENO_GENERAL, env, status);
	path = get_path(cmd->expanded_args[0]);
	if (path.err.no != ENO_SUCCESS)
		(err_handler(path.err.msg, path.err.cause),
			get_out(data, single_exit_s(path.err.no, ADD), env, status));
	if (execve(path.path, cmd->expanded_args, env) == -1)
		get_out(data, single_exit_s(1, ADD), env, status);
}

int	exec_pipe(t_data *data, t_cmd *cmd)
{
	t_cmd	*c;
	int		fd[4];
	int		status;

	(void)cmd;
	status = 0;
	c = data->cmd;
	fd[2] = dup(STDIN_FILENO);
	while (c)
	{
		ft_printf("cmd = %s\n\n", c->expanded_args[0]);
		if (pipe(fd) != 0)
			return (ft_putstr_fd("__ERROR_PIPE__:\nError pipe.\n", 2), 3);
		// signal(SIGINT, SIG_IGN);
		c->pid = fork();
		// set_sig_child();
		if (c->pid == -1)
			return (ft_putstr_fd("__ERROR_FORK__:\nError fork.\n", 2), 4);
		if (!c->pid)
		{
			if (!c->expanded_args)
			{
				if (check_redir(c) != ENO_SUCCESS)
					single_exit_s(ENO_GENERAL, ADD);
				clean_program(data);
				exit(single_exit_s(0, GET));
				// return ((single_exit_s(0, GET) && ENO_GENERAL));
			}
			else if (is_builtin(c->expanded_args[0]))
			{
				if (check_redir(c) == ENO_SUCCESS)
					single_exit_s(exec_builtin(data, c), ADD);
				else
					single_exit_s(ENO_GENERAL, ADD);
				clean_program(data);
				exit(single_exit_s(0, GET));
			}
			exec_pipe_child(data, c, &status, fd);
		}
		swap_pipes(fd);
		single_exit_s(close_n_exit_s(c, status), ADD);
		c = c->next;
	}
	close(fd[2]);
	c = data->cmd;
	ft_printf("here\n\n");
	while (c)
		waitpid(c->pid, &fd[3], 0);
	return (get_exit_status(single_exit_s(0, GET)));
}
