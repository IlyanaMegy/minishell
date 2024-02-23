/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:13 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/31 12:12:14 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cleaned_str_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i + 1] && ((str[i] == '"' && str[i + 1] == '"')
				|| (str[i] == '\'' && str[i + 1] == '\'')))
			i += 2;
		else
			len += (i++ || 1);
	}
	return (len);
}

/**
 * @note   do clean empty strings or quotes from str
 * @param  str: given string
 * @retval cleaned string
*/
char	*clean_empty_strs(char *str)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2]) || (str[0] == '"'
			&& str[1] == '"' && !str[2]))
		return (str);
	tmp = ft_calloc(cleaned_str_len(str) + 1, sizeof(char));
	if (!tmp)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\'' && str[i
				+ 1] == '\''))
			i += 2;
		else
			tmp[j++] = str[i++];
	}
	free(str);
	return (tmp);
}
