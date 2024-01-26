/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:00:49 by ilymegy           #+#    #+#             */
/*   Updated: 2023/08/17 22:06:55 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned int	size;
	char			*ptr;
	int				i;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	ptr = malloc((size + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
