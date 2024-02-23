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

/**
 * @note   do clean empty strings or quotes from str
 * @param  str: given string
 * @retval cleaned string
*/
char	*clean_empty_strs(char *str, int i, int j)
{
	char	*tmp;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2]) || (str[0] == '"'
			&& str[1] == '"' && !str[2]))
		return (str);
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!tmp)
		return (free(str), NULL);
	while (str[i])
	{
		if ((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\'' && str[i
				+ 1] == '\''))
		{
			if (i != 0 && str[i - 1] == ' ' && str[i - 2])
				(tmp[j - 1] = '|', tmp[j++] = ' ');
			i += 2;
			if (str[i] && str[i] == ' ' && str[i + 1])
				(tmp[j++] = ' ', tmp[j++] = '|', i++);
		}
		else
			tmp[j++] = str[i++];
	}
	return (free(str), tmp);
}
