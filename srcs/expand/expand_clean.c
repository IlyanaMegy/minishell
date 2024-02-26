/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:13 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/23 13:15:42 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	quotes_in_quotes(int *i, char **str, int *j, char **tmp)
{
	int		a;
	char	q1;
	char	q2;

	a = *i;
	if (((*str)[a] == '"' && (*str)[a + 1] == '\'') || ((*str)[a] == '\''
			&& (*str)[a + 1] == '"'))
	{
		q1 = (*str)[a];
		q2 = (*str)[++a];
		while ((*str)[a] && (*str)[a] != q1)
			a++;
		if ((*str)[a] != q1)
		{
			q1 = 0;
			q2 = 0;
			return (0);
		}
		(*tmp)[(*j)++] = (*str)[(*i)++];
		while ((*str)[*i] != q1)
			(*tmp)[(*j)++] = (*str)[(*i)++];
		(*tmp)[(*j)++] = (*str)[(*i)++];
		return (1);
	}
	return (0);
}

static int	if_string_empty(char *str)
{
	if ((str[0] == '\'' && str[1] == '\'' && !str[2]) || (str[0] == '"'
			&& str[1] == '"' && !str[2]))
		return (1);
	return (0);
}

static void	add_pipes_remove_quotes(int *i, char **str, int *j, char **tmp)
{
	if ((*i) != 0 && (*str)[(*i) - 1] == ' ' && (*str)[(*i) - 2])
	{
		(*tmp)[(*j) - 1] = ';';
		(*tmp)[(*j)++] = ' ';
	}
	(*i) += 2;
	if ((*str)[(*i)] && (*str)[(*i)] == ' ' && (*str)[(*i) + 1])
	{
		(*tmp)[(*j)++] = ';';
		(*i)++;
	}
}

/**
 * @note   do clean empty strings or quotes from str
 * @param  str: given string
 * @retval cleaned string
*/
char	*clean_empty_strs(char *str, int i, int j)
{
	char	*tmp;

	if (if_string_empty(str))
		return (str);
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!tmp)
		return (free(str), NULL);
	while (str[i])
	{
		if (!quotes_in_quotes(&i, &str, &j, &tmp))
		{
			if ((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\'' && str[i
						+ 1] == '\''))
				add_pipes_remove_quotes(&i, &str, &j, &tmp);
			else
				tmp[j++] = str[i++];
		}
	}
	return (free(str), tmp);
}
