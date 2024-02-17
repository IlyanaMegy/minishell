/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:30:09 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/17 17:18:25 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   clean the env list
 * @param  e: environment list to clear
 * @retval NULL env
*/
t_env	*clean_env(t_env *e)
{
	t_env	*tmp;

	if (e == NULL)
		return (NULL);
	while (e != NULL)
	{
		tmp = e->next;
		if (e->content != NULL)
			free(e->content);
		free(e->name);
		free(e);
		e = tmp;
	}
	e = NULL;
	return (e);
}

/**
 * @note   clean the data struct
 * @param  e: struct to clear
 * @retval NULL data
*/
void	free_data(t_data *data)
{
	if (data && data->user_input)
		free_ptr(data->user_input);
	if (data && data->token)
		lstclear_token(&data->token, &free_ptr);
	if (data && data->cmd)
		lstclear_cmd(&data->cmd, &free_ptr);
}

/**
 * @note   free double array string
 * @param  map: given double array string
 * @retval None
*/
void	free_tab(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free_ptr(map[i]);
			i++;
		}
		free(map);
		map = NULL;
	}
	return ;
}

/**
 * @brief
 * @note   free pointer
 * @param  ptr: given pointer
 * @retval None
*/
void	free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

/**
 * @note   clean up all t_data structure, env and history
 * @param  data: t_data structure
 * @retval None
*/
void	clean_program(t_data *data)
{
	close(data->stdin);
	close(data->stdout);
	free_data(data);
	clean_env(single_env(NULL, GET));
	rl_clear_history();
}
