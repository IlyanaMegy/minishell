/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:20:15 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/27 21:20:34 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   get variable content from the environment for cd builtin
 * @param  var_name: variable name
 * @retval content is yes, NULL is no variable with that name
*/
char	*get_var_content_from_env_cd(char *var_name)
{
	t_env	*e;

	e = single_env(NULL, GET);
	while (e)
	{
		if (!ft_strcmp(e->name, var_name) && e->print_it == 1)
			return (e->content);
		e = e->next;
	}
	return (NULL);
}

/**
 * @note   changing environment's variable pwd content by the current pwd
 * @param  old_cmd: old current directory
 * @retval 1 is err getcwd, 0 is ok
*/
int	change_pwd(char *old_cwd)
{
	char	*cwd;
	int		i;
	char	*pwd_path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(old_cwd), 1);
	i = 0;
	pwd_path = get_var_content_from_env("PWD");
	if (pwd_path)
	{
		free(old_cwd);
		replace_var_in_env("OLDPWD", pwd_path, &i);
		i = 0;
		return (replace_var_in_env("PWD", cwd, &i), free(cwd), 0);
	}
	else
	{
		free(pwd_path);
		free(cwd);
		replace_var_in_env("OLDPWD", old_cwd, &i);
		free(old_cwd);
	}
	return (0);
}

/**
 * @note   go to $HOME directory
 * @retval 1 if no path for $HOME or failed when chdir, 0 is ok
*/
int	cd_home(void)
{
	char	*home;
	int		i;
	char	*pwd_path;
	char	*null_path;

	i = 0;
	pwd_path = NULL;
	home = get_var_content_from_env_cd("HOME");
	if (!home)
		return (err_handler(ERR_PATH, "cd"), 1);
	if (chdir(home) == 0)
	{
		pwd_path = get_var_content_from_env("PWD");
		if (pwd_path)
		{
			replace_var_in_env("OLDPWD", pwd_path, &i);
			i = 0;
			return (replace_var_in_env("PWD", home, &i), 0);
		}
		null_path = ft_strdup("");
		replace_var_in_env("OLDPWD", null_path, &i);
		return (free(null_path), 0);
	}
	return (1);
}

/**
 * @note   handling "cd -" command, inverting PWD && OLDPWD
 * @retval exit status
*/
int	handle_cd_dash(void)
{
	char	*old_pwd;
	int		i;
	char	*pwd_path;
	char	*null_path;

	i = 0;
	old_pwd = ft_strdup(get_var_content_from_env_cd("OLDPWD"));
	if (!old_pwd)
		return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO),
			1);
	if (chdir(old_pwd) == 0)
	{
		(ft_putstr_fd(old_pwd, 2), ft_putchar_fd('\n', 2));
		pwd_path = get_var_content_from_env("PWD");
		if (pwd_path)
		{
			replace_var_in_env("OLDPWD", pwd_path, &i);
			i = 0;
			return (replace_var_in_env("PWD", old_pwd, &i), free(old_pwd), 0);
		}
		null_path = ft_strdup("");
		replace_var_in_env("OLDPWD", null_path, &i);
		return (free(null_path), free(old_pwd), 0);
	}
	return (1);
}

/**
 * @note   change directory
 * @param  cmd: path of destination directory
 * @retval 1 is err getcd or home path or too much args or no path, 0 is ok
*/
int	ft_cd(char **cmd)
{
	int		i;
	char	*err_msg;
	char	*old_cwd;

	i = 0;
	err_msg = NULL;
	while (cmd[i])
		i++;
	if (i > 2)
		return (err_handler(ERR_ARGS, "cd"), 1);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
		return (cd_home());
	if (!ft_strcmp(cmd[1], "-"))
		return (handle_cd_dash());
	old_cwd = getcwd(NULL, 0);
	if (!old_cwd)
		return (cdpwd_error_chdir_getcwd(1), 1);
	if (chdir(cmd[1]) != 0)
	{
		err_msg = ft_strjoin("cd: ", cmd[1]);
		return (err_handler(ERR_NOFILEDIR, err_msg), free(old_cwd),
			free(err_msg), 1);
	}
	return (change_pwd(old_cwd));
}
