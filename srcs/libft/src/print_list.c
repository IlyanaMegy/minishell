/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:57:28 by ilymegy           #+#    #+#             */
/*   Updated: 2023/09/05 13:57:31 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	print_list(t_list *mylist)
{
	t_list	*lst;

	lst = mylist;
	while (lst->next)
	{
		ft_printf("%s --> ", (char *)lst->content);
		lst = lst->next;
	}
	ft_printf("%s\n", (char *)lst->content);
}
