/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:10:45 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/11 18:10:47 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   getting after checking the path in the environment of that command
 * @param  cmd: command in question
 * @param  path: PATH in the environment
 * @retval path of cmd
*/
static char	*get_env_path(char *cmd, char *path)
{
	int		i;
	char	*exec;
	char	*path_part;
	char	**split_path;

	i = -1;
	split_path = ft_split(path, ':');
	while (split_path[++i])
	{
		path_part = ft_strjoin(split_path[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (check_exec(exec, true) == ENO_SUCCESS)
		{
			ft_free_tab(split_path);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(split_path);
	single_exit_s(ENO_NOT_FOUND, ADD);
	return (err_handler(ERR_NOCMD, cmd), NULL);
}

/**
 * @note   check if the path is an executable
 * @param  file: the path
 * @param  cmd: ?
 * @retval exit status
*/
int	check_exec(char *file, bool cmd)
{
	if (!*file)
		return (err_handler(ERR_NOFILEDIR, file), ENO_GENERAL);
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == -1)
			return (err_handler(ERR_PERM_DENIED, file), ENO_CANT_EXEC);
		return (ENO_SUCCESS);
	}
	if (cmd)
		return (err_handler(ERR_NOCMD, file), ENO_NOT_FOUND);
	return (err_handler(ERR_NOFILEDIR, file), ENO_NOT_FOUND);
}

/**
 * @note   get path of this command
 * @param  cmd: command in question
 * @retval the path or NULL if error
*/
char	*get_path(char *cmd)
{
	char	*content;

	if (*cmd == '\0')
	{
		single_exit_s(ENO_NOT_FOUND, ADD);
		return (err_handler(ERR_NOCMD, "\'\'"), NULL);
	}
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (single_exit_s(check_exec(cmd, false), ADD), cmd);
	content = get_var_content_from_env("PATH");
	if (content)
		return (get_env_path(content, cmd));
	single_exit_s(ENO_NOT_FOUND, ADD);
	return (err_handler(ERR_NOFILEDIR, "\'\'"), NULL);
}
