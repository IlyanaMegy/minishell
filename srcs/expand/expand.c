/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:39:02 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/18 12:39:05 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   reveal string after handling simple and double quotes and dollars
 * @param  str: given string
 * @retval cleaned and revealed string
*/
// static char	*pre_handling(char *str)
// {
// 	char	*res;
// 	int		i;

// 	i = 0;
// 	res = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 			res = ft_strjoin_n_free(res, handle_single_quotes(str, &i));
// 		else if (str[i] == '"')
// 			res = ft_strjoin_n_free(res, handle_double_quotes(str, &i));
// 		else if (str[i] == '$')
// 			res = ft_strjoin_n_free(res, handle_dollar(str, &i));
// 		else
// 			res = ft_strjoin_n_free(res, handle_normal_str(str, &i));
// 	}
// 	return (res);
// }

int	add_to_tmplst(t_list *tmp, char *str)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (1);
	new->content = str;
	new->next = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		tmp = new;
	return (0);
}

char	**lst_to_tab(t_list *lst)
{
	t_list	*tmp;
	char	**tab;
	int		i;

	i = 0;
	tab = ft_calloc((ft_lstsize(lst) + 1), sizeof(char *));
	tmp = lst;
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->content);
		free(tmp->content);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	print_tab(tab);
	return (tab);
}

/**
 * @note   handling expander here
 * @param  str: given string
 * @retval splited and clean 2D array
*/
char **	expander(char *str)
{
	int		i;
	t_list	*tmp;

	char **res;
	char **t;
	// str = pre_handling(str);
	// if (!str)
	// 	return (NULL);
	// ft_printf("res = \'%s\'\n\n", str);
	// str = ft_clean_empty_strs(str);
	// if (!str)
	// 	return (NULL);
	// exp = ft_split(str, ' ');
	// // exp = expand_split(str);
	// ft_printf("exp[1] = \"%s\"\n", exp[1]);
	// free(str);
	// if (!exp)
	// 	return (NULL);
	// return (exp);
	i = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			ft_lstadd_back(&tmp, ft_lstnew(handle_single_quotes(str, &i)));
		else if (str[i] == '"')
			ft_lstadd_back(&tmp, ft_lstnew(handle_double_quotes(str, &i)));
		else if (str[i] == '$')
			ft_lstadd_back(&tmp, ft_lstnew(handle_dollar(str, &i)));
		else
		{
			t = ft_split(handle_normal_str(str, &i), ' ');
			while (t)
			{
				// ft_printf("*t = %s\n", *t);
				ft_lstadd_back(&tmp, ft_lstnew(*t));
				t++;
			}
			free_tab(t);
			ft_printf("here");
		}
	}
	ft_list_remove_if(&tmp, " ", ft_strcmp);
	print_tab(lst_to_tab(tmp));
	res = lst_to_tab(tmp);
	ft_printf("res[0] = %s\n", res[0]);
	return (res);
}
