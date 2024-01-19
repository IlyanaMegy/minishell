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
 * @note   handling string with single quotes
 * @param  s: given string
 * @param  i: index
 * @retval cleaned and revealed str
 */
char	*handle_single_quotes(char *s, int *i)
{
	int	start;

	start = ++(*i);
	while (s[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(s, start, *i - start - 1));
}

/**
 * @note   handling string with double quotes
 * @param  s: given string
 * @param  i: index
 * @retval cleaned and revealed str
 */
static char	*handle_double_quotes_str(char *s, int *i)
{
	int	start;

	start = *i;
	while (s[*i] != '"' && s[*i] != '$')
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

/**
 * @note   handling string with double quotes or dollar
 * @param  s: given string
 * @param  i: index
 * @retval cleaned and revealed str
 */
char	*handle_double_quotes(char *s, int *i)
{
	char	*res;

	res = ft_strdup("");
	(*i)++;
	while (s[*i] != '"')
	{
		if (s[*i] == '$')
			res = ft_strjoin_n_free(res, handle_dollar(s, i));
		else
			res = ft_strjoin_n_free(res, handle_double_quotes_str(s, i));
	}
	(*i)++;
	return (ft_strjoin_n_free(res, ft_strdup("")));
}

/**
 * @note   handling string with dollar
 * @param  s: given string
 * @param  i: index
 * @retval cleaned and revealed str
 */
char	*handle_dollar(char *s, int *i)
{
	int		start;
	char	*var;
	char	*env_content;

	(*i)++;
	if (ft_isdigit(s[*i]) || s[*i] == '@')
		return ((*i)++, ft_strdup(""));
	else if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(single_exit_s(0, GET)));
	}
	else if (!ft_isalnum(s[*i]) && s[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	var = ft_substr(s, start, *i - start);
	if (!var)
		return (ft_strdup(""));
	env_content = get_var_content_from_env(var);
	if (!env_content)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(env_content));
}

/**
 * @note   handling normal string
 * @param  s: given string
 * @param  i: index
 * @retval cleaned and revealed str
 */
char	*handle_normal_str(char *s, int *i)
{
	int	start;

	start = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != '$')
		(*i)++;
	return (ft_substr(s, start, *i - start));
}
