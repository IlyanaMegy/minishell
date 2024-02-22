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
	int	extra;
	int	len;

	i = 0;
	extra = 0;
	len = 0;
	while (str[i])
	{
		if (str[i + 1] && ((str[i] == '"' && str[i + 1] == '"')
				|| (str[i] == '\'' && str[i + 1] == '\'')))
		{
			extra = 1;
			i += 2;
			len++;
		}
		else
			len += (i++ || 1);
	}
	ft_printf("len = %d\n\n", len);
	return (len + extra);
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
	char	extra;

	extra = 0;
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
		if (str[i + 1] && ((str[i] == '"' && str[i + 1] == '"')
				|| (str[i] == '\'' && str[i + 1] == '\'')))
		{
			if (!extra)
			{
				tmp[j++] = str[i];
				extra = str[i];
			}
			i += 2;
		}
		else
			tmp[j++] = str[i++];
	}
	if (extra)
		tmp[j] = extra;
	free(str);
	return (tmp);
}
