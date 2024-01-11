/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:25:58 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/04 16:26:03 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note	get the linked list's size 
 * @param 	lst: linked list to study
 * @retval	the size obviously...
*/
int	ms_lstsize(t_env *lst)
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

char	**env_to_tab(t_env *env_lst)
{
	t_env *tmp;
	char **env_tab;
	char *joined;
	int i;

	i = 0;
	env_tab = ft_calloc((ms_lstsize(env_lst) + 1), sizeof(char *));
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

void	print_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		ft_printf("%s\n", tab[i]);
}
