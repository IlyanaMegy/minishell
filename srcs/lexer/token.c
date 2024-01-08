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
	if (c == '\'' && quote_status == NONE)
		quote_status = SINGLE;
	else if (c == '\"' && quote_status == NONE)
		quote_status = DOUBLE;
	else if (c == '\'' && quote_status == SINGLE)
		quote_status = NONE;
	else if (c == '\"' && quote_status == DOUBLE)
		quote_status = NONE;
	return (quote_status);
}

int save_sep(t_token **token_lst, char *s, int index, int type)
{
	int		len;
	char	*sep;

	// len for malloc if type is >> or <<
	if (type == APPEND || type == HEREDOC)
		len = 2;
	// len for malloc for all other separators
	else
		len = 1;
	sep = ft_substr(s, index, len);
	if (!sep)
		return (1);
	lst_add_back_token(token_lst, lst_new_token(sep, type, NONE));
	return (0);
}

int save_word(t_token **token_lst, char *s, int index, int start)
{
	char *word;

	word = ft_substr(s, start, index - start);
	if (!word)
		return (1);
	lst_add_back_token(token_lst, lst_new_token(word, WORD, NONE));
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
	// Set quote status to NONE
	quote_status = NONE;
	while (i <= end)
	{
		// Change quote_status if single or double quote is found
		quote_status = set_quote_status(quote_status, s[i]);
		// Save word or separator if quote_status is set to NONE
		// + set new index for next token
		if (quote_status == NONE)
		{
			// Type returns 0 if s[i] is not a separator
			type = is_separator(s, i);
			// Execute if type is a separator
			if (type)
			{
				// if current index is not 0, is a separator
				// and char before this one is NOT a separator:
				// save the word as token in structure
				if (i && !is_separator(s, i - 1))
					save_word(&data->token, s, i, start);
				// if type is a separator, save separator as token in structure

				// A DECOMMENTER POUR GESTION DES SEPARATEURS
				// if (type == APPEND || type == HEREDOC || type == PIPE
				// 	|| type == INPUT || type == TRUNC || type == END_STR)
				if (type == END_STR)
				{
					save_sep(&data->token, s, i, type);
					// if type is >> or << increase index +1
					if (type == APPEND || type == HEREDOC)
						i++;
				}
				// New index for next token
				start = i + 1;
			}
		}
		i++;
	}
	// TODO If couldn't find matching quote at the end of the str, print error message
	if (quote_status != NONE)
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
