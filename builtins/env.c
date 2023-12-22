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

/**
 * @note   do display the environment
 * @param  env: environment list
 * @retval None
*/
void	ft_env(t_env *env)
{
	t_env_var	*e;
	char		*shlvl;

	e = env->f_var;
	while (e)
	{
		if (!ft_strcmp(e->name, "SHLVL") && e->print_it == 1)
		{
			shlvl = ft_itoa(ft_atoi(e->content) - 1);
			if (shlvl)
			{
				ft_printf("%s=%s\n", e->name, shlvl);
				free(shlvl);
			}
			else
				ft_printf("%s=%s\n", e->name, e->content);
		}
		else if (e->print_it == 1)
			ft_printf("%s=%s\n", e->name, e->content);
		e = e->next;
	}
}

/**
 * @note   create a new var
 * @param  name: variable name
 * @param  content: variable content
 * @param  print_it: do we print it or not ?
 * @retval new variable just created
*/
t_env_var	*create_var(char *name, char *content, int print_it)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (free(new), NULL);
	new->content = ft_strdup(content);
	if (!new->content)
		return (free(new->name), free(new), NULL);
	new->next = NULL;
	new->prev = NULL;
	new->print_it = print_it;
	return (new);
}

/**
 * @note   add a new var to env list
 * @param  env: environment list
 * @param  name: variable name
 * @param  content: variable content
 * @param  print_it: do we print it or not ?
 * @retval 0 is ok, 1 is err malloc
*/
int	add_var_to_env(t_env *env, char *name, char *content, int print_it)
{
	t_env_var	*var;
	t_env_var	*e;

	var = create_var(name, content, print_it);
	if (var == NULL)
		return (1);
	e = env->f_var;
	if (env->f_var)
	{
		while (e->next)
			e = e->next;
		e->next = var;
		var->prev = e;
	}
	else
		env->f_var = var;
	return (0);
}

/**
 * @note   get variable name and content
 * @param  tmp_name: variable name container
 * @param  tmp_content: variable content container
 * @param  arg: current argument from environment
 * @param  i: index
 * @retval 1 is err malloc, 0 is ok
*/
int	get_var(char **tmp_name, char **tmp_content, char *arg, int i)
{
	char	*shlvl;

	*tmp_name = ft_strndup(arg, i);
	if (*tmp_name == NULL)
		return (1);
	if (!ft_strcmp(*tmp_name, "SHLVL"))
	{
		shlvl = ft_itoa(ft_atoi(arg + i + 1) + 1);
		if (!shlvl)
			*tmp_content = ft_strdup(arg + i + 1);
		else
			*tmp_content = shlvl;
	}
	else
		*tmp_content = ft_strdup(arg + i + 1);
	if (*tmp_content == NULL)
	{
		free(*tmp_name);
		return (1);
	}
	return (0);
}

/**
 * @note   get environment from arg_env and stock to env list
 * @param  arg_env: environment origin from minishell argument
 * @param  env: environment list
 * @retval 1 is err malloc, 0 is ok
*/
int	get_env(char **arg_env, t_env *env)
{
	int		i[2];
	char	**tmp_env;
	int		err_malloc;

	i[0] = 0;
	err_malloc = 0;
	env->f_var = NULL;
	tmp_env = malloc(sizeof(char *) * 3);
	if (!tmp_env)
		return (1);
	while (arg_env[i[0]])
	{
		i[1] = 0;
		while (arg_env[i[0]][i[1]] != '=')
			i[1]++;
		err_malloc = get_var(&tmp_env[0], &tmp_env[1], arg_env[i[0]], i[1]);
		if (err_malloc)
			break ;
		err_malloc = add_var_to_env(env, tmp_env[0], tmp_env[1], 1);
		free(tmp_env[1]);
		free(tmp_env[0]);
		if (err_malloc)
			break ;
		i[0]++;
	}
	free(tmp_env);
	return (err_malloc);
}
