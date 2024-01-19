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

char	*ft_strcat(char *dest, const char *src)
{
	ft_memcpy(dest + ft_strlen(dest), src, ft_strlen(src) + 1);
	return (dest);
}
