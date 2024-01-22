/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:39:02 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/19 23:25:38 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   reveal string after handling simple and double quotes and dollars
 * @param  str: given string
 * @retval cleaned and revealed string
 */
static char	*pre_handling(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			res = ft_strjoin_n_free(res, handle_single_quotes(str, &i));
		else if (str[i] == '"')
			res = ft_strjoin_n_free(res, handle_double_quotes(str, &i));
		else if (str[i] == '$')
			res = ft_strjoin_n_free(res, handle_dollar(str, &i));
		else
			res = ft_strjoin_n_free(res, handle_normal_str(str, &i));
	}
	return (res);
}

/**
 * @note   handling expander here
 * @param  args: given args
 * @retval revealed 2D array
 */
char	**expander(char **args)
{
	char	**exp_args;
	int		i;

	i = 0;
	if (!args[0])
		return (args);
	exp_args = malloc(sizeof(char *) * (double_array_len(args) + 1));
	if (!exp_args)
		return (NULL);
	while (args[i])
	{
		exp_args[i] = pre_handling(args[i]);
		i++;
	}
	exp_args[i] = NULL;
	return (exp_args);
}
