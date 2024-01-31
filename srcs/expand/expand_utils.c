/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:51:44 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/19 23:22:27 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   is the character a valid one or not ?
 * @param  c: given character
 * @retval true or false
*/
bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

/**
 * @brief  
 * @note   handle normal string
 * @param  str: given string
 * @param  *i: index
 * @retval substring found
*/
char	*handle_normal_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

/**
 * @brief  
 * @note   handle double quotes string
 * @param  str: given string
 * @param  *i: index
 * @retval substring found
*/
static char	*handle_dquote_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

/**
 * @brief  
 * @note   handle simple quotes string
 * @param  str: given string
 * @param  *i: index
 * @retval substring found
*/
char	*handle_squotes(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

/**
 * @brief  
 * @note   handle double quotes or dollars string
 * @param  str: given string
 * @param  *i: index
 * @retval substring found
*/
char	*handle_dquotes(char *str, size_t *i)
{
	char	*ret;

	ret = ft_strdup("\"");
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			ret = strjoin_f(ret, handle_dollar(str, i, true));
		else
			ret = strjoin_f(ret, handle_dquote_str(str, i));
	}
	(*i)++;
	return (strjoin_f(ret, ft_strdup("\"")));
}
