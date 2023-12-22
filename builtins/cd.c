/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:20:15 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/13 16:20:17 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @note   changing variable pwd content by currend pwd
 * @param  env: environment list
 * @retval 1 is err getcwd, 0 is ok
*/
int	change_pwd(t_env *env)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	i = 0;
	return (replace_var_in_env(env, "PWD", cwd, &i), 0);
}

/**
 * @note   go to $HOME directory
 * @param  env: environment list
 * @retval 1 if no path for $HOME, 0 is ok
*/
int	cd_home(t_env *env)
{
	char	*home;
	int		i;

	i = 0;
	replace_var_in_env(env, "OLDPWD", get_var_content_from_env(env, "PWD"), &i);
	home = get_var_content_from_env(env, "HOME");
	if (!home)
		return (err_handler(ERR_PATH, "cd"), 1);
	if (chdir(home) == 0)
		return (replace_var_in_env(env, "PWD", home, &i), 0);
	return (1);
}

/**
 * @note   change directory
 * @param  env: environment list
 * @param  cmd: path of destination directory
 * @retval 1 is err getcd or get home path or too much args or not found path,
	0 is ok
*/
int	ft_cd(t_env *env, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
		return (err_handler(ERR_ARGS, "cd"), 1);
	if (!cmd[1])
		return (cd_home(env));
	if (chdir(cmd[1]) != 0)
		return (err_handler(ERR_NOFILEDIR, "cd"), 1);
	i = 0;
	replace_var_in_env(env, "OLDPWD", get_var_content_from_env(env, "PWD"), &i);
	return (change_pwd(env));
}
