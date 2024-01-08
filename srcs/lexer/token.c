/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:21:11 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/08 14:22:09 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	else if (s[i] == '\0')
		return (END_STR);
	else
		return (0);
}

int	set_quote_status(int quote_status, char c)
{
	if (c == '\'' && quote_status == DEFAULT)
		quote_status = SINGLE;
	else if (c == '\"' && quote_status == DEFAULT)
		quote_status = DOUBLE;
	else if (c == '\'' && quote_status == SINGLE)
		quote_status = DEFAULT;
	else if (c == '\"' && quote_status == DOUBLE)
		quote_status = DEFAULT;
	return (quote_status);
}

int	save_sep(t_token **token_lst, char *s, int index, int type)
{
	int		i;
	char	*sep;
	int		len;

	i = 0;
	// if type is >> or << malloc is bigger
	if (type == APPEND || type == HEREDOC)
		len = 2;
	// for all other separators
	else
		len = 1;
	sep = malloc(sizeof(char) * len + 1);
	if (!sep)
		return (1);
	while (i < len)
		sep[i++] = s[index++];
	sep[i] = '\0';
	lst_add_back_token(token_lst, lst_new_token(sep, type, DEFAULT));
	return (0);
}

int	save_word(t_token **token_lst, char *s, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	while (start < index)
		word[i++] = s[start++];
	word[i] = '\0';
	lst_add_back_token(token_lst, lst_new_token(word, WORD, DEFAULT));
	return (0);
}

bool	tokenize_input(t_data *data, char *s)
{
	int	i;
	int	end;
	int	start;
	int	quote_status;
	int	type;

	i = 0;
	start = 0;
	end = ft_strlen(s);
	// Set quote status to default
	quote_status = DEFAULT;
	while (i <= end)
	{
		// Change quote_status if single or double quote is found
		quote_status = set_quote_status(quote_status, s[i]);
		// Save word or separator if quote_status is set to DEFAULT
		// + set new index for next token
		if (quote_status == DEFAULT)
		{
			// Type returns 0 if s[i] is not a separator
			type = is_separator(s, i);
			// Execute if type is a separator
			if (type)
			{
				// if current index exists, is a separator
				// and char before this one is NOT a separator:
				// save the word as token in structure
				if (i && !is_separator(s, i - 1))
					save_word(&data->token, s, i, start);
				// if type is a separator, save separator as token in structure
				if (type == APPEND || type == HEREDOC || type == PIPE
					|| type == INPUT || type == TRUNC || type == END_STR)
					{
						save_sep(&data->token, s, i, type);
						// If type is >> or << increase index +1
						if (type == APPEND || type == HEREDOC)
							i++;
					}
				// New index for next token
				start = i++;
			}
		}
		i++;
	}
	// TODO If couldn't find matching quote at the end of the str, print error message
	if (quote_status != DEFAULT)
	{
		// if quote_status == DOUBLE: unexpected EOF while looking for matching \"
		// if quote_status == SINGLE: unexpected EOF while looking for matching \'
		ft_printf("Quote error to handle\n");
		return (false);
	}
	free(data->user_input);
	data->user_input = NULL;
	return (true);
}
