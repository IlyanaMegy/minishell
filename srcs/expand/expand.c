/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:39:02 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/18 12:39:05 by ilymegy          ###   ########.fr       */
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
 * @param  str: given string
 * @retval splited and clean 2D array
*/
char	**expander(char *str)
{
	char	**exp;

	str = pre_handling(str);
	if (!str)
		return (NULL);
	str = ft_clean_empty_strs(str);
	if (!str)
		return (NULL);
	exp = expand_split(str);
	free(str);
	if (!exp)
		return (NULL);
	return (exp);
}
