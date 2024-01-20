/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:07:59 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/18 14:08:01 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   skip the word
 * @param  s: given string
 * @param  *i: index
 * @retval None
*/
static void	skip_da_word(char *s, int *i)
{
	char	quotes;

	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		else
		{
			quotes = s[(*i)++];
			while (s[*i] != quotes)
				(*i)++;
			(*i)++;
		}
	}
}

/**
 * @note   allocate s string after splited to strs
 * @param  s: given string
 * @param  strs: splited string
 * @retval splited string
*/
static char	**gimme_gimme(char *s, char **strs)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			start = i;
			skip_da_word(s, &i);
			strs[j] = ft_calloc(i - start + 1, sizeof(char *));
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
 * @note   
 * @param  s: given string
 * @param  strs: 2D string to fill
 * @param  *i: index s
 * @param  j: index strs
 * @retval None
*/
static void	words_fill(char *s, char **strs, int *i, int j)
{
	char	quotes;
	int		k;

	k = 0;
	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			strs[j][k++] = s[(*i)++];
		else
		{
			quotes = s[(*i)++];
			strs[j][k++] = quotes;
			while (s[(*i)] != quotes)
				strs[j][k++] = s[(*i)++];
			strs[j][k++] = s[(*i)++];
		}
	}
}

/**
 * @note   fill strs from given string
 * @param  s: given string 
 * @param  strs: 2D string to fill
 * @retval splited string
*/
static char	**fill_it(char *s, char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && strs[j])
	{
		if (s[i] != ' ')
		{
			words_fill(s, strs, &i, j);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

/**
 * @note   do split given string
 * @param  s: given string
 * @retval cleaned and splited string
*/
char	**expand_split(char *s)
{
	int		count;
	int		i;
	char	**strs;
	char	**tmp;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && ++count)
			skip_da_word(s, &i);
		while (s[i] && s[i] == ' ')
			i++;
	}
	strs = ft_calloc(count + 1, sizeof(char *));
	tmp = strs;
	strs = gimme_gimme(s, strs);
	if (!strs || !count)
		return (free_tab(tmp), NULL);
	return (fill_it(s, strs));
}
