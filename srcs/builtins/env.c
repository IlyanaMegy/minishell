/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:21:04 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/27 21:25:51 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   do display the environment from t_env linked list
 * @retval None
 */
void	ft_env(void)
{
	t_env	*e;

	e = single_env(NULL, GET);
	while (e)
	{
		if (e->print_it == 1)
			ft_printf("%s=%s\n", e->name, e->content);
		e = e->next;
	}
}
