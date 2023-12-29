/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:21:31 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/27 20:35:01 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   will add/replace variable to environment
 * @param  var: variable name and content
 * @param  print_it: do we print it or not ?
 * @retval None
*/
void	add_var_to_env_list(char **var, int print_it, int *append)
{
	if (var_is_in_env(var[0]) && print_it)
	{
		replace_var_in_env(var[0], var[1], append);
		return ;
	}
	if (var[1] && ft_strcmp(var[1], ""))
		add_var_to_env(var[0], var[1], print_it);
	else
		add_var_to_env(var[0], "", print_it);
}

/**
 * @note   get name and content of the var then add it to the environment
 * @param  arg: variable
 * @param  append: += or not ?
 * @retval 0 no error
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
		add_var_to_env_list(var, 1, append);
	}
	else if (!arg[i])
	{
		var[0] = ft_strdup(arg);
		if (!var[0])
			return (1);
		var[1] = ft_strdup("");
		if (!var[1])
			return (free(var[0]), 1);
		add_var_to_env_list(var, 0, append);
	}
	return (free(var[0]), free(var[1]), 0);
}

/**
 * @note   check if the argument is correct
 * @param  arg: variable
 * @retval 1 is ok, 0 is an err
*/
int	check_var_name(char *arg, int *append)
{
	int	i;

	i = 0;
	if (!ft_isalpha(*arg) && *arg != '_')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '+')
			return (0);
		if (arg[i] == '+' && *append)
			return (0);
		if (arg[i] == '+' && !(*append))
			++(*append);
		i++;
	}
	return (1);
}

/**
 * @note   simply display environment, print_it == 0 vars included
 * @retval None
 */
void	display_export(void)
{
	t_env	*e;
	t_env	*dirty_e;

	dirty_e = copy_my_lst(single_env(NULL, 0));
	if (dirty_e != NULL && ms_lstsize(dirty_e) == ms_lstsize(single_env(NULL, 0)))
	{
		e = get_sorted_env(&dirty_e);
		while (e)
		{
			if (!(strcmp(e->name, "_")) && strlen(e->name) == 1)
				ft_printf("");
			else
				ft_printf("%s=\"%s\"\n", e->name, e->content);
			e = e->next;
		}
		clean_env(dirty_e);
	}
	// clean_env(e);
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
		if (!check_var_name(cmd[i], &append))
		{
			exit_status = 1;
			err_handler(ERR_EXPORT, cmd[i]);
		}
		else
			exit_status = extract_var(cmd[i], &append);
		i++;
	}
	return (exit_status);
}
