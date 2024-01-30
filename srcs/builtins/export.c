/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:21:31 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/19 21:41:32 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   will add/replace variable to environment
 * @param  var: variable name and content
 * @param  print_it: do we print it or not ?
 * @retval exit status 0 is ok, 1 not ok
*/
int	add_var_to_env_list(char **var, int print_it, int *append)
{
	int	exit_s;

	exit_s = 0;
	if (var_is_in_env(var[0]) && print_it)
	{
		exit_s = replace_var_in_env(var[0], var[1], append);
		return (free(var[0]), free(var[1]), exit_s);
	}
	exit_s = add_var_to_env(var[0], var[1], print_it);
	return (free(var[0]), free(var[1]), exit_s);
}

/**
 * @note   get name and content of the var then add it to the environment
 * @param  name: variable name
 * @param  content: variable content
 * @retval 1 case strdup or strndup failed, 0 is ok
*/
int	extract_var_no_content(char *arg, int *append)
{
	char	*var[2];

	var[0] = ft_strdup(arg);
	if (!(var[0]))
		return (1);
	var[1] = ft_strdup("");
	if (!(var[1]))
		return (free(var[0]), 1);
	return (add_var_to_env_list(var, 0, append));
}

/**
 * @note   get name and content of the var then add it to the environment
 * @param  arg: variable
 * @param  append: += or not ?
 * @retval 1 case strdup or strndup failed, 0 is ok
*/
int	extract_var(char *arg, int *append)
{
	int		i;
	char	*var[2];

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] && arg[i] == '=')
	{
		var[0] = ft_strndup(arg, i - *append);
		if (!var[0])
			return (1);
		if (!arg[i + 1])
			var[1] = ft_strdup("");
		else
			var[1] = ft_strdup(arg + i + 1);
		if (!var[1])
			return (free(var[0]), 1);
		return (add_var_to_env_list(var, 1, append));
	}
	else if (!arg[i] && !var_is_in_env(arg))
		return (extract_var_no_content(arg, append));
	return (0);
}

/**
 * @note   check if the argument is correct
 * @param  arg: variable
 * @param  append: is it += ?
 * @retval exit status
*/
int	invalid_var_name(char *arg, int *append)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		return (2);
	if (!ft_isalpha(*arg) && *arg != '_')
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '+')
			return (1);
		if (arg[i] == '+' && *append)
			return (1);
		if (arg[i] == '+' && !(*append) && arg[i + 1] != '=')
			return (1);
		if (arg[i] == '+' && !(*append))
			++(*append);
		i++;
	}
	return (0);
}

/**
 * @note   export a var in environment or display environment with tmp vars
 * @param  cmd: export cmd and all args
 * @retval exit status
*/
int	ft_export(char **cmd)
{
	int	i;
	int	exit_status;
	int	append;

	if (!cmd[1])
		return (display_export(), 0);
	i = 1;
	while (cmd[i])
	{
		append = 0;
		exit_status = invalid_var_name(cmd[i], &append);
		if (exit_status == 1)
			err_handler(ERR_EXPORT, cmd[i]);
		else if (exit_status == 2)
			err_handler(ERR_EXPORT_OPT, cmd[i]);
		else
			extract_var(cmd[i], &append);
		i++;
	}
	return (exit_status);
}
