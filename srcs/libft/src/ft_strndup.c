/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:41:24 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/19 20:41:26 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

char	*ft_strndup(const char *s1, int n)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (s1[i] && i < (int)n)
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	while (j < i)
	{
		res[j] = s1[j];
		j++;
	}
	res[j] = '\0';
	return (res);
}
