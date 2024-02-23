/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:21:11 by ltorkia           #+#    #+#             */
/*   Updated: 2024/02/23 15:03:12 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	pre_check_token(char *s, int index)
{
	if (s[index] && !s[index + 1])
	{
		if (s[0] == '!')
			return (single_exit_s(1, ADD), false);
		else if (s[0] == ':')
			return (single_exit_s(0, ADD), false);
	}
	return (true);
}

static int	save_sep(t_token **token_lst, char *s,
	int index, t_token_type sep_type)
{
	int		len;
	char	*sep;
	t_token	*new_token;

	if (sep_type == APPEND || sep_type == HEREDOC)
		len = 2;
	else
		len = 1;
	sep = ft_substr(s, index, len);
	if (!sep)
		return (-1);
	new_token = lst_new_token(sep, sep_type);
	if (!new_token)
		return (free_ptr(sep), -1);
	lst_add_back_token(token_lst, new_token);
	index += len;
	return (index);
}

static int	save_word(t_token **token_lst, char *s, int index)
{
	int		start;
	char	*word;
	t_token	*new_token;

	start = index;
	while (s[index] && !is_separator(s, index))
	{
		if (is_quote(s, index))
		{
			if (!ignore_quotes(s, &index))
				return (err_quote(s[index]), -1);
		}
		else
			index++;
	}
	word = ft_substr(s, start, index - start);
	if (!word)
		return (-1);
	new_token = lst_new_token(word, WORD);
	if (!new_token)
		return (free_ptr(word), -1);
	lst_add_back_token(token_lst, new_token);
	return (index);
}

static int	save_token(t_data *data, char *s, int index)
{
	int		sep_type;

	sep_type = is_separator(s, index);
	if (ft_isspace(s[index]))
		index = ignore_spaces(s, index);
	else if (sep_type)
		index = save_sep(&data->token, s, index, sep_type);
	else
		index = save_word(&data->token, s, index);
	return (index);
}

bool	tokenize_input(t_data *data, char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (ignore_spaces(s, 0) == -1)
		return (single_exit_s(0, ADD), false);
	str = trim_spaces(s);
	if (!str)
		return (single_exit_s(1, ADD), false);
	if (!pre_check_token(str, i))
		return (free_ptr(str), false);
	while (str[i])
	{
		i = save_token(data, str, i);
		if (i == -1)
			return (free_ptr(str), single_exit_s(1, ADD), false);
	}
	free_ptr(str);
	if (!check_syntax(data->token))
		return (false);
	return (true);
}
