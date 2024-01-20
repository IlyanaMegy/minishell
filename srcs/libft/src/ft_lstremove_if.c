/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:18:51 by ilymegy           #+#    #+#             */
/*   Updated: 2023/05/09 14:18:53 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*cur;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	cur = *begin_list;
	if (cmp(cur->content, data_ref) == 0)
	{
		*begin_list = cur->next;
		free(cur);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
		cur = *begin_list;
		ft_list_remove_if(&cur->next, data_ref, cmp);
	}
}
