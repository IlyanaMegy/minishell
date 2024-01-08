/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:55:25 by ilymegy           #+#    #+#             */
/*   Updated: 2023/08/17 22:01:20 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

int	words_count(const char *s, char sep)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == sep)
			++s;
		if (*s)
			++count;
		while (*s && *s != sep)
			++s;
	}
	return (count);
}

char const	*case_quote(char const *tmp, char const *s, char ***res)
{
	tmp = ++s;
	while (*tmp && *tmp != '\'')
		++tmp;
	if (*tmp == '\'' || tmp > s)
	{
		**res = ft_substr(s, 0, tmp - s);
		if (!(**res))
			return (NULL);
		++(*res);
	}
	return (tmp);
}

char const	*case_else(char const *tmp, char const *s, char sep, char ***res)
{
	while (*tmp && *tmp != sep)
		++tmp;
	if (*tmp == sep || tmp > s)
	{
		**res = ft_substr(s, 0, tmp - s);
		if (!(**res))
			return (NULL);
		++(*res);
	}
	return (tmp);
}

static int	give_to(char **tab, char const *s, char sep)
{
	char		**res;
	char const	*tmp;

	tmp = s;
	res = tab;
	while (*tmp)
	{
		while (*s == sep)
			++s;
		tmp = s;
		if (*s == '\'')
			s = case_quote(tmp, s, &res);
		else
			s = case_else(tmp, s, sep, &res);
		if (!s)
			return (1);
	}
	*res = NULL;
	return (0);
}

char	**ft_split(char *s, char sep)
{
	char	**res;
	int		err;

	if (!s)
		return (NULL);
	err = 0;
	res = (char **)malloc((words_count(s, sep) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	err = give_to(res, s, sep);
	if (err)
		return (NULL);
	return (res);
}
