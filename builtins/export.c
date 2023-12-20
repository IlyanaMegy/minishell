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
	printf("err export\n");
	return (1);
}


/**
 * @note   check if the argument is correct
 * @param  *arg: 
 * @retval 1 is ok, 0 is an err
*/
int	check_export_arg(char *arg)
{
	int	i;

	i = 1;
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

int	ft_export(t_env *env, char **av)
{
	int i;
	int exit_status;

	if (!av[1])
		return (display_export(env), 0);
	i = 1;
	while (av[i])
	{
		if (!check_exp_arg(av[i]))
			exit_status = print_export_err_msg(av[i]);
		i++;
	}
	return (exit_status);
}