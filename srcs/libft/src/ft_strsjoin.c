/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:35:18 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/18 17:35:20 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

char	*ft_strsjoin(char **strs, char *sep)
{
	int		i;
	size_t	join_len;
	char	*join;

	join_len = 0;
	i = -1;
	while (strs[++i] != NULL)
	{
		join_len += ft_strlen(strs[i]);
		if (strs[i + 1] != NULL)
			join_len += ft_strlen(sep);
	}
	join = (char *)malloc(sizeof(char) * (join_len + 1));
	if (join == NULL)
		return (NULL);
	join[0] = '\0';
	i = -1;
	while (strs[++i] != NULL)
	{
		ft_strcat(join, strs[i]);
		if (*strs[i] != '\0' && strs[i + 1] != NULL)
			ft_strcat(join, sep);
	}
	return (join);
}
