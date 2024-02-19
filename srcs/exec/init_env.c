/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:00:08 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/27 18:00:10 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   create a new var
 * @param  name: variable name
 * @param  content: variable content
 * @param  print_it: do we print it or not ?
 * @retval new variable just created
 */
t_env	*create_var(char *name, char *content, int print_it)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
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
 * @param  name: variable name
 * @param  content: variable content
 * @param  print_it: do we print it or not ?
 * @retval 0 is ok, 1 is err malloc
*/
int	add_var_to_env(char *name, char *content, int print_it)
{
	t_env	*var;
	t_env	*e;

	var = create_var(name, content, print_it);
	if (var == NULL)
		return (1);
	var->next = NULL;
	e = single_env(NULL, GET);
	if (e)
	{
		while (e->next)
			e = e->next;
		var->prev = e;
		e->next = var;
	}
	else
		single_env(var, ADD);
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
static int	get_var(char **tmp_name, char **tmp_content, char *arg, int i)
{
	char	*shlvl;

	shlvl = NULL;
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
		return (free(*tmp_name), 1);
	return (0);
}

/**
 * @note   add in t_env linked list missed but VIP variables
 * @param  var_name: variable name
 * @param  var_content: variable content
 * @param  pwd: is it pwd that we add ?
 * @retval exit status
*/
static int	add_if_missing(char *var_name, char *var_content, int pwd)
{
	char	*name;
	char	*content;

	name = ft_strdup(var_name);
	if (!name)
		return (1);
	if (!pwd)
	{
		content = ft_strdup(var_content);
		if (!content)
			return (free(name), 1);
	}
	else
		content = var_content;
	if (!get_var_content_from_env(name))
	{
		if (add_var_to_env(name, content, 1))
			return (free(name), free(content), 1);
	}
	else
		return (free(name), free(content), 0);
	return (0);
}

/**
 * @note   get environment from arg_env and stock to env list
 * @param  arg_env: environment origin from minishell argument
 * @retval 1 is err malloc, 0 is ok
 */
int	get_env(char **arg_env)
{
	int		i[2];
	char	**tmp_env;

	i[0] = 0;
	tmp_env = malloc(sizeof(char *) * 3);
	if (!tmp_env)
		return (1);
	while (arg_env[i[0]])
	{
		i[1] = 0;
		while (arg_env[i[0]][i[1]] != '=')
			i[1]++;
		if (get_var(&tmp_env[0], &tmp_env[1], arg_env[i[0]], i[1]))
			return (free(tmp_env), 1);
		if (add_var_to_env(tmp_env[0], tmp_env[1], 1))
			return (free(tmp_env[0]), free(tmp_env[1]), free(tmp_env), 1);
		(free(tmp_env[0]), free(tmp_env[1]));
		i[0]++;
	}
	if (!var_is_in_env("OLD_PWD") && extract_var_no_content("OLDPWD", 0))
		return (free(tmp_env), 1);
	if (add_if_missing("PWD", getcwd(NULL, 0), 1) || add_if_missing("SHLVL",
			"1", 0) || add_if_missing("_", "/usr/bin/env", 0))
		return (free(tmp_env), 1);
	return (free(tmp_env), 0);
}
