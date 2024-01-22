/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnullstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:03:28 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/22 19:03:32 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

int	ft_isnullstr(char c, int quotes)
{
	if (((c == '"') || (c == '\'')) && !quotes)
		return (1);
	return (0);
}
