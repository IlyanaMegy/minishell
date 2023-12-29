/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:18:12 by ilymegy           #+#    #+#             */
/*   Updated: 2023/08/23 00:00:27 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

long int	ft_atoi(const char *str)
{
	int			minus;
	long int	res;

	minus = 1;
	res = 0;
	while (*str == 32 || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -minus;
		str++;
	}
	while (*str >= 48 && *str <= 57)
		res = res * 10 + *str++ - 48;
	if (*str++)
		return (0);
	return (res * minus);
}
