/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:21:11 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/23 15:03:00 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ignore_spaces(char *s, int index)
{
	while (s[index])
	{
		if (!ft_isspace(s[index]))
			return (index);
		index++;
	}
	return (-1);
}

char	*trim_spaces(char *s)
{
	int		len;
	int		i;
	char	*new_s;

	i = 0;
	len = ft_strlen(s) - 1;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (len >= i && ft_isspace(s[len]))
		len--;
	new_s = ft_substr(s, i, len - i + 1);
	if (!new_s)
		return (NULL);
	return (new_s);
}

int	is_separator(char *s, int i)
{
	if (((s[i] > 8 && s[i] < 14) || s[i] == 32))
		return (WHITESPACE);
	else if (s[i] == '|')
		return (PIPE);
	else if (s[i] == '<' && s[i + 1] == '<')
		return (HEREDOC);
	else if (s[i] == '>' && s[i + 1] == '>')
		return (APPEND);
	else if (s[i] == '<')
		return (INPUT);
	else if (s[i] == '>')
		return (TRUNC);
	else
		return (0);
}

bool	is_quote(char *s, int index)
{
	if (s[index] == '\'' || s[index] == '"')
		return (true);
	return (false);
}

bool	ignore_quotes(char *s, int *index)
{
	char	quote;

	quote = s[*index];
	if (ft_strchr(s + *index + 1, quote))
	{
		(*index)++;
		while (s[*index] != quote)
			(*index)++;
		(*index)++;
		return (true);
	}
	return (false);
}
