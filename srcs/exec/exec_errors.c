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
