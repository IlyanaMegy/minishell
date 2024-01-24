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
 * @note   count words after handling simple and double quotes and dollars
 * @param  str: given string
 * @retval words count of str
 */
int	count_words(char *str)
{
	int		i;
	char	*res;

	i = 0;
	if (!str || !str[i])
		return (1);
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			res = ft_strjoin_n_free(res, handle_single_quotes(str, &i));
		else if (str[i] == '"')
			res = ft_strjoin_n_free(res, handle_double_quotes(str, &i));
		else if (str[i] == '$')
			res = ft_strjoin_n_free(res, handle_dollar(str, &i, 0));
		else
			res = ft_strjoin_n_free(res, handle_normal_str(str, &i));
	}
	if (res[0] == '"' && res[1] == '"' && !res[2])
		return (free(res), 0);
	return (free(res), 1);
}

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
	if (!str || !str[i])
		return (res);
	while (str[i])
	{
		if (str[i] == '\'')
			res = ft_strjoin_n_free(res, handle_single_quotes(str, &i));
		else if (str[i] == '"')
			res = ft_strjoin_n_free(res, handle_double_quotes(str, &i));
		else if (str[i] == '$')
			res = ft_strjoin_n_free(res, handle_dollar(str, &i, 0));
		else
			res = ft_strjoin_n_free(res, handle_normal_str(str, &i));
	}
	if (res[0] == '"' && res[1] == '"' && !res[2])
		return (free(res), NULL);
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
	char	*tmp;
	int		j;

	i = -1;
	j = 0;
	if (!args[0])
		return (args);
	while (args[++i])
		j += count_words(args[0]);
	if (j == 0)
		return (NULL);
	exp_args = malloc(sizeof(char *) * (j + 1));
	if (!exp_args)
		return (NULL);
	(i = -1, j = 0);
	while (args[++i])
	{
		tmp = pre_handling(args[i]);
		if (tmp != NULL)
			(exp_args[j++] = pre_handling(args[i]), free(tmp));
	}
	exp_args[j] = NULL;
	return (exp_args);
}
