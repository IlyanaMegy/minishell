#include "../../inc/minishell.h"

void	ft_waitpid(t_data *data)
{
	t_cmd	*c;
	int		err;

	c = data->cmd;
	while (c)
	{
		waitpid(c->pid, &err, 0);
		c = c->next;
	}
}

void	ft_close_all(int fd[3])
{
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

void	handle_weird_cases(t_data *data, t_cmd *cmd, int *status)
{
	if (!cmd->expanded_args)
	{
		if (check_redir(cmd) != ENO_SUCCESS)
			single_exit_s(ENO_GENERAL, ADD);
		clean_program(data);
		exit(single_exit_s(0, GET));
	}
	else if (is_builtin(cmd->expanded_args[0]))
	{
		if (check_redir(cmd) == ENO_SUCCESS)
			single_exit_s(exec_builtin(data, cmd), ADD);
		else
			single_exit_s(ENO_GENERAL, ADD);
		clean_program(data);
		exit(single_exit_s(0, GET));
	}
	if (cmd_is_dot(cmd->expanded_args[0]))
		get_out(data, ENO_MISS_CMD, NULL, status);
	if (cmd_is_dir(cmd->expanded_args[0]))
		get_out(data, ENO_CANT_EXEC, NULL, status);
}

void	exec_pipe_child(t_data *data, t_cmd *cmd, int *status, int fd[3])
{
	t_path	path;
	char	**env;

	if (!cmd->prev)
		dup2(fd[1], STDOUT_FILENO);
	if (!cmd->next)
		dup2(fd[2], STDIN_FILENO);
	else if (cmd->next && cmd->prev)
	{
		dup2(fd[2], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	ft_close_all(fd);
	handle_weird_cases(data, cmd, status);
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

int	exec_pipe(t_data *data)
{
	t_cmd	*c;
	int		fd[3];
	int		status;

	status = 0;
	c = data->cmd;
	fd[2] = dup(STDIN_FILENO);
	while (c)
	{
		if (pipe(fd) != 0)
			return (ft_putstr_fd("__ERROR_PIPE__:\nError pipe.\n", 2), 3);
		// signal(SIGINT, SIG_IGN);
		c->pid = fork();
		// set_sig_child();
		if (c->pid == -1)
			return (ft_putstr_fd("__ERROR_FORK__:\nError fork.\n", 2), 4);
		if (!c->pid)
			exec_pipe_child(data, c, &status, fd);
		swap_pipes(fd);
		single_exit_s(close_n_exit_s(c, status), ADD);
		c = c->next;
	}
	close(fd[2]);
	ft_waitpid(data);
	return (get_exit_status(single_exit_s(0, GET)));
}
