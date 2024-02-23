/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:11:03 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/23 13:15:15 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   do skip word from string to increment index
 * @param  s: given string
 * @param  *i: s index
 * @retval None
*/
static void	skip_word(char const *s, size_t *i)
{
	char	quotes;

	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		else
		{
			quotes = s[(*i)++];
			while (s[(*i)] != quotes)
				(*i)++;
			(*i)++;
		}
	}
}

/**
 * @note   allocate size from s to strs
 * @param  s: given string
 * @param  strs: result double array
 * @retval allocated double array
*/
static char	**allocate_size(char const *s, char **strs)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			start = i;
			skip_word(s, &i);
			strs[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!strs[j])
				return (NULL);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

/**
 * @note   fill double array from string
 * @param  s: given string
 * @param  strs: result double array
 * @param  *i: s index
 * @param  j: strs index
 * @retval None
*/
static void	gimme_that(const char *s, char **strs, size_t *i, size_t j)
{
	char	quotes;
	size_t	k;

	k = 0;
	while (s[(*i)] && s[(*i)] != ' ')
	{
		if (s[(*i)] != '\'' && s[(*i)] != '"')
			strs[j][k++] = s[(*i)++];
		else
		{
			quotes = s[(*i)++];
			strs[j][k++] = quotes;
			if (s[(*i)])
			{
				while (s[(*i)] && (s[(*i)] != quotes))
					strs[j][k++] = s[(*i)++];
				strs[j][k++] = s[(*i)];
				if (s[(*i)])
					(*i)++;
			}
		}
	}
}

/**
 * @note   fill double array from string
 * @param  s: given string
 * @param  strs: result double array
 * @retval filled double array
*/
static char	**fill_it(char const *s, char **strs)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && strs[j])
	{
		if (s[i] != ' ')
		{
			gimme_that(s, strs, &i, j);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

/**
 * @note   split string into double array string
 * @param  s: given string
 * @retval splitted string into double array string
*/
char	**expander_split(char const *s)
{
	size_t	count;
	char	**strs;
	char	**free_me;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && ++count)
			skip_word(s, &i);
		while (s[i] && s[i] == ' ')
			i++;
	}
	strs = ft_calloc(count + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	free_me = strs;
	strs = allocate_size(s, strs);
	if (!strs || !count)
		return (free_tab(free_me), NULL);
	return (fill_it(s, strs));
}
