/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:51:31 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/23 13:14:28 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   join first and second strings into one and free them
 * @param  s1: first string
 * @param  s2: second string
 * @retval joined string
*/
char	*strjoin_f(char *s1, char *s2)
{
	char	*joined;
	size_t	total_length;
	size_t	i;
	size_t	j;

	if (s1 && !s2)
		return (free(s1), NULL);
	if (!s1 || !s2)
		return (NULL);
	total_length = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = ft_calloc(total_length, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = 0;
	return (free(s1), free(s2), joined);
}

char	*handle_dollar(char *str, size_t *i, bool quotes)
{
	size_t	start;
	char	*var;
	char	*env_val;

	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
		return ((*i)++, ft_strdup(""));
	else if (str[*i] == '?')
		return ((*i)++, ft_itoa(single_exit_s(0, GET)));
	else if ((str[*i] == '"' || str[*i] == '\'') && !quotes)
		return (ft_strdup(""));
	else if (!is_valid_var_char(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (is_valid_var_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	env_val = get_var_content_from_env(var);
	if (!env_val)
	{
		if (str[*i] != '\0' && !str[*i + 1] && !quotes)
			(*i)++;
		return (free(var), ft_strdup(""));
	}
	return (free(var), ft_strdup(env_val));
}

static char	*pre_expand(char *str)
{
	char	*ret;
	size_t	i;

	ret = ft_strdup("");
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = strjoin_f(ret, handle_squotes(str, &i));
		else if (str[i] == '"')
			ret = strjoin_f(ret, handle_dquotes(str, &i));
		else if (str[i] == '$')
			ret = strjoin_f(ret, handle_dollar(str, &i, false));
		else
			ret = strjoin_f(ret, handle_normal_str(str, &i));
		if (!ret)
			return (NULL);
	}
	return (ret);
}

static char	*remove_spaces_cmd(char *str)
{
	int		i;
	size_t	count;
	int		j;
	char	*res;

	i = 0;
	count = ft_strlen(str);
	while (str[i])
		if (str[i++] == ' ' && !str[i])
			count--;
	if (count == ft_strlen(str))
		return (str);
	res = ft_calloc(count + 1, sizeof(char));
	if (!res)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			res[j++] = str[i++];
		else
			i++;
	}
	return (free(str), res);
}

char	**expand(char *str)
{
	char	**expanded;
	size_t	i;
	size_t	j;

	str = pre_expand(str);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	str = clean_empty_strs(str, i, j);
	expanded = expander_split(str);
	free(str);
	if (!expanded)
		return (NULL);
	i = 0;
	while (expanded[i])
	{
		expanded[i] = strip_quotes(expanded[i]);
		if (i == 0)
			expanded[i] = remove_spaces_cmd(expanded[i]);
		i++;
	}
	return (expanded);
}
