/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:21:04 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/13 16:21:06 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_env *env)
{
	t_env_var	*tmp;
	char		*shlvl;

	tmp = env->f_var;
	while (tmp)
	{
		if (tmp->print_it == 1)
		{
			write(1, tmp->name, ft_strlen(tmp->name));
			write(1, "=", 1);
			if (!ft_strcmp(tmp->name, "SHLVL"))
			{
				shlvl = ft_itoa(ft_atoi(tmp->content) - 1);
				write(1, shlvl, ft_strlen(shlvl));
				free(shlvl);
			}
			else
				write(1, tmp->content, ft_strlen(tmp->content));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}

/**
 * @note   create a new var
 * @param  char* name: 
 * @param  char* content: 
 * @param  int print_it: 
 * @retval new variable just created
*/
t_env_var	*create_var(char *name, char *content, int print_it)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->content = ft_strdup(content);
	new->next = NULL;
	new->print_it = print_it;
	return (new);
}

/**
 * @note   add a new var to env list
 * @param  t_env* env: 
 * @param  char* name: 
 * @param  char* content: 
 * @param  int print_it: 
 * @retval None
*/
void	add_var_to_env(t_env *env, char *name, char *content, int print_it)
{
	t_env_var	*var;
	t_env_var	*tmp;

	var = create_var(name, content, print_it);
	// var->next = NULL;
	tmp = env->f_var;
	if (env->f_var)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = var;
	}
	else
		env->f_var = var;
}

/**
 * @note   get environment from arg_env and stock to env list
 * @param  char** arg_env: 
 * @param  t_env* env: 
 * @retval None
*/
void	get_env(char **arg_env, t_env *env)
{
	int		i;
	int		j;
	char	**tmp_env;

	i = 0;
	tmp_env = malloc(sizeof(char *) * 3);
	if (!tmp_env)
		return ;
	env->f_var = NULL;
	while (arg_env[i])
	{
		j = 0;
		while (arg_env[i][j] != '=')
			j++;
		tmp_env[0] = ft_strndup(arg_env[i], j);
		if (!ft_strcmp(tmp_env[0], "SHLVL"))
			tmp_env[1] = ft_itoa(ft_atoi(arg_env[i] + j + 1) + 1);
		else
			tmp_env[1] = ft_strdup(arg_env[i] + j + 1);
		add_var_to_env(env, tmp_env[0], tmp_env[1], 1);
		free(tmp_env[0]);
		free(tmp_env[1]);
		i++;
	}
	free(tmp_env);
}
