/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:25:58 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/19 23:25:49 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note	get the linked list's size 
 * @param 	lst: linked list to study
 * @retval	the size obviously...
*/
int	envlst_len(t_env *lst)
{
	size_t	count;
	t_env	*clone;

	clone = lst;
	count = 0;
	while (clone)
	{
		count++;
		clone = clone->next;
	}
	return (count);
}

/**
 * @note   recursively copy t_env linked list to new t_env list
 * @param  src: t_env linked list to copy
 * @retval return new t_env list
*/
t_env	*copy_my_lst(t_env *src)
{
	t_env	*copy;

	if (src == NULL)
		return (NULL);
	else
	{
		copy = create_var(src->name, src->content, src->print_it);
		if (copy == NULL)
			return (NULL);
		copy->next = copy_my_lst(src->next);
		return (copy);
	}
}

/**
 * @note   convert of t_env linked list to 2D array
 * @param  env_lst: t_env linked list
 * @retval 2D array of t_env linked list
*/
char	**env_to_tab(t_env *env_lst)
{
	t_env	*tmp;
	char	**env_tab;
	char	*joined;
	int		i;

	i = 0;
	env_tab = ft_calloc((envlst_len(env_lst) + 1), sizeof(char *));
	if (!env_tab)
		return (NULL);
	tmp = env_lst;
	while (tmp)
	{
		if (tmp->print_it)
		{
			joined = ft_strjoin(tmp->name, "=");
			env_tab[i] = ft_strjoin(joined, tmp->content);
			free(joined);
			i++;
		}
		tmp = tmp->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

/**
 * @note   get 2D array length
 * @param  arr: given 2D array
 * @retval its length
*/
int	double_array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
