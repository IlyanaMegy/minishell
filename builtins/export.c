/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:21:31 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/13 16:21:33 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_export_err_msg(char *arg)
{
	ft_printf("err export %s\n", arg);
	return (1);
}


/**
 * @note   check if the argument is correct
 * @param  *arg: 
 * @retval 1 is ok, 0 is an err
*/
int	check_export_var_name(char *arg)
{
	int	i;

	i = 0;
	ft_printf("av[0] = %s\n", arg);
	if (!ft_isalpha(*arg) && *arg != '_')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @note   simply display environment, print_it == 0 vars included
 * @param  t_env* env: 
 * @retval None
 */
void	display_export(t_env *env)
{
	t_env_var	*e;

	e = env->f_var;
	get_sorted_env(&e);
	while (e)
	{
		if (!(strcmp(e->name, "_")) && strlen(e->name) == 1)
			ft_printf("");
		else if (!ft_strcmp(e->name, "SHLVL"))
			ft_printf("%s=\"%s\"\n", e->name, ft_itoa(ft_atoi(e->content) - 1));
		else
			ft_printf("%s=\"%s\"\n", e->name, e->content);
		e = e->next;
	}
}

int	ft_export(t_env *env, char **cmd)
{
	int i;
	int exit_status;
	

	// ft_printf("av[0] = %s\n", av[0]);
	if (!cmd[1])
		return (display_export(env), 0);
	i = 1;
	while (cmd[i])
	{
		if (!check_export_var_name(cmd[i]))
			exit_status = print_export_err_msg(cmd[i]);
		i++;
	}
	return (exit_status);
}