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
	char	*ret;
	size_t	dstsize;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2])
		|| (str[0] == '"' && str[1] == '"' && !str[2]))
		return (str);
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!tmp)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
		tmp[j++] = str[i++];
	free(str);
	dstsize = ft_strlen(tmp) + 1;
	ret = ft_calloc(dstsize, sizeof(char));
	if (!ret)
		return (free(tmp), NULL);
	return (ft_strlcpy(ret, tmp, dstsize), free(tmp), ret);
}
