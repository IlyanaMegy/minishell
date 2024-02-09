/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:26:09 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/06 10:18:45 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   update, clear or return current t_env linked list
 * @param  env: environment list
 * @param  mode: ADD or GET
 * @retval return current t_env list
*/
t_env	*single_env(t_env *env, int mode)
{
	static t_env	*single_env = NULL;

	if (mode == ADD)
		single_env = env;
	else if (mode == GET)
		return (single_env);
	return (single_env);
}

/**
 * @note   update or return current exit status
 * @param  exit_s: exit status
 * @param  mode: ADD or GET
 * @retval return current exit status
*/
int	single_exit_s(int exit_s, int mode)
{
	static int	single_exit_s = 0;

	if (mode == ADD)
		single_exit_s = exit_s;
	if (mode == GET)
		return (single_exit_s);
	return (single_exit_s);
}
