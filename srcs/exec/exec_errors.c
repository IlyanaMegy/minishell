/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:13:52 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/31 12:13:53 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   check if first argument is a directory
 * @param  cmd: given first argument
 * @retval true or false
*/
bool	cmd_is_dir(char *cmd)
{
	DIR		*dir;
	char	*start_msg;
	char	*err_msg;
	char	*msg;

	start_msg = ft_strdup("minishell: ");
	err_msg = ft_strjoin(cmd, ": Is a directory\n");
	msg = ft_strjoin(start_msg, err_msg);
	dir = opendir(cmd);
	if (dir != NULL)
	{
		closedir(dir);
		ft_putstr_fd(msg, STDERR_FILENO);
		(free(start_msg), free(err_msg), free(msg));
		return (true);
	}
	(free(start_msg), free(err_msg), free(msg));
	return (closedir(dir), false);
}

/**
 * @note   check if first argument is alone dot
 * @param  cmd: given first argument
 * @retval true or false
*/
bool	cmd_is_dot(char *cmd)
{
	char	*start_msg;
	char	*err_msg;
	char	*msg;

	start_msg = ft_strdup("minishell: ");
	err_msg = ft_strjoin(cmd, ": filename argument required\n");
	msg = ft_strjoin(start_msg, err_msg);
	if (!ft_strcmp(cmd, "."))
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		(free(start_msg), free(err_msg), free(msg));
		return (true);
	}
	(free(start_msg), free(err_msg), free(msg));
	return (false);
}

/**
 * @note   close here_doc's fd if exist get and return exit status
 * @param  cmd: current command
 * @param  status: given exit status
 * @retval exit status
*/
int	close_n_exit_s(t_data *data, t_cmd *cmd, int status)
{
	close(data->stdin);
	close(data->stdout);
	if (cmd->io_list && cmd->io_list->here_doc)
		close(cmd->io_list->here_doc);
	return (get_exit_status(status));
}

int	print_heredoc_error(void)
{
	char	*err_hd;

	err_hd = "minishell: warning: here-document delimited by";
	ft_putstr_fd(err_hd, 2);
	ft_putstr_fd(" end-of-file (wanted `eof')\n", 2);
	return (1);
}
