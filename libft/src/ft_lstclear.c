/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:20:50 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/09 20:20:52 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;
	t_list	*temp;

	t = *lst;
	if (t == NULL)
		return ;
	while (t != NULL)
	{
		temp = t->next;
		del(t);
		t = temp;
	}
	*lst = NULL;
}
