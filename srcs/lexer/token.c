/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:21:11 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/15 19:25:23 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	save_sep(t_token **token_lst, char *s, int index, int sep_type)
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

int	save_word(t_token **token_lst, char *s, int index)
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

bool	tokenize_input(t_data *data, char *s)
{
	int		i;
	int		sep_type;

	i = 0;
	while (s[i])
	{
		sep_type = is_separator(s, i);
		if (ft_isspace(s[i]))
			i = ignore_spaces(s, i);
		else if (sep_type)
			i = save_sep(&data->token, s, i, sep_type);
		else
			i = save_word(&data->token, s, i);
		if (i == -1)
			return (false);
	}
	// *	DEBUG : Print the current token list
	print_token(data->token);
	if (!check_syntax(data->token))
		return (false);
	return (true);
}
