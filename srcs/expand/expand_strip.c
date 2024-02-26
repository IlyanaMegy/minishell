/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:53:55 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/31 11:53:57 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   get length of result string cleaned from quotes
 * @param  str: given string
 * @retval length
*/
static size_t	unquoted_strlen(char *str)
{
	size_t	i;
	size_t	len;
	char	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (!quotes)
				quotes = str[i++];
			else if (str[i] == quotes)
				quotes = ((i++) && 0);
			else
				len += (i++ || 1);
		}
		else
			len += (i++ || 1);
	}
	return (len);
}

/**
 * @note   add characters to result string
 * @param  str: given string
 * @param  *i: index given str
 * @param  res: result string
 * @param  *j: index res str
 * @retval None
*/
static void	unquote_fill_it(char *str, size_t *i, char *res, size_t *j)
{
	char	quotes;

	quotes = str[(*i)++];
	while (str[*i] != quotes)
		res[(*j)++] = str[(*i)++];
	(*i)++;
}

static char	*remove_trash(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ';')
		{
			res[j++] = ' ';
			i++;
		}
		else
			res[j++] = str[i++];
	}
	return (free(str), res);
}

/**
 * @note   remove quotes from string
 * @param  str: given string
 * @retval cleaned string
*/
char	*strip_quotes(char *str)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = remove_trash(str);
	if (!str)
		return (NULL);
	res = ft_calloc(1 + unquoted_strlen(str), sizeof(char));
	if (!res)
		return (free(str), NULL);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			(unquote_fill_it(str, &i, res, &j));
		else
			res[j++] = str[i++];
	}
	return (free(str), res);
}
