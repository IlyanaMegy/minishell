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

/**
 * @note   get next sorted var
 * @param  **head: 
 * @param  *node: 
 * @retval None
*/
void	sorted_var(t_env_var **head, t_env_var *node)
{
	t_env_var	tmp;
	t_env_var	*curr;

	curr = &tmp;
	tmp.next = *head;
	while (curr->next != NULL && ft_strcmp(curr->next->name, node->name) < 0)
		curr = curr->next;
	node->next = curr->next;
	curr->next = node;
	*head = tmp.next;
}

/** 
 * @note   get a alphabetically sorted env
 * @param  t_env** head: 
 * @retval 
*/
void	get_sorted_env(t_env_var **head)
{
	t_env_var	*res;
	t_env_var	*tmp;
	t_env_var	*curr;

	curr = *head;
	res = NULL;
	while (curr != NULL)
	{
		tmp = curr->next;
		sorted_var(&res, curr);
		curr = tmp;
	}
	*head = res;
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

void	ft_export(t_env *env)
{
	display_export(env);
}