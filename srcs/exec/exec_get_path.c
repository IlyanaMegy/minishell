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
static t_path	get_env_path(char *cmd, char *path)
{
	int		i;
	t_err	err;
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
		err = check_exec(exec, true);
		if (err.no == ENO_SUCCESS)
			return (free_tab(split_path), (t_path){(t_err){ENO_SUCCESS, 55,
				exec}, exec});
		free(exec);
	}
	free_tab(split_path);
	return ((t_path){(t_err){ENO_NOT_FOUND, ERR_NOCMD, cmd}, NULL});
}

/**
 * @note   check if the path is an executable
 * @param  file: the executable path
 * @param  cmd: is it cmd ?
 * @retval t_err error status
*/
t_err	check_exec(char *file, bool cmd)
{
	if (!*file)
		return ((t_err){ENO_GENERAL, ERR_NOFILEDIR, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == -1)
			return ((t_err){ENO_CANT_EXEC, ERR_PERM_DENIED, file});
		return ((t_err){ENO_SUCCESS, 55, NULL});
	}
	if (cmd)
		return ((t_err){ENO_NOT_FOUND, ERR_NOCMD, file});
	return ((t_err){ENO_NOT_FOUND, ERR_NOFILEDIR, file});
}

/**
 * @note   get path of this command
 * @param  cmd: command in question
 * @retval the path or NULL if error
*/
t_path	get_path(char *cmd)
{
	char	*content;

	if (*cmd == '\0')
		return ((t_path){(t_err){ENO_NOT_FOUND, ERR_NOCMD, cmd}, NULL});
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return ((t_path){check_exec(cmd, false), cmd});
	content = get_var_content_from_env("PATH");
	if (content)
		return (get_env_path(cmd, content));
	return ((t_path){(t_err){ENO_NOT_FOUND, ERR_NOFILEDIR, cmd}, NULL});
}
