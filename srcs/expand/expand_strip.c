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
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (!quotes)
				quotes = str[i++];
			else if (str[i] == quotes && !str[i + 1])
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
	if (str[*i])
	{
		while (str[*i] && (str[*i] != quotes || (str[*i] == quotes && str[*i
					+ 1])))
			res[(*j)++] = str[(*i)++];
		(*i)++;
	}
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
	res = ft_calloc(1 + unquoted_strlen(str), sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && str[(i + 1)])
			unquote_fill_it(str, &i, res, &j);
		else
			res[j++] = str[i++];
	}
	return (free(str), res);
}
