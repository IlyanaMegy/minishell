#include "../../inc/minishell.h"

static bool handle_spaces(char **user_input)
{
	int     i;
	int     len;
	char    *temp;

	i = 0;
	len = ft_strlen((*user_input));
	while ((*user_input)[i])
	{
		if (!ft_isspace((*user_input)[i]))
		{
			temp = (*user_input);
			(*user_input) = ft_substr(temp, i, len);
			free(temp);
			temp = NULL;
			if (!(*user_input))
				return (false);
			return (true);
		}
		i++;
	}
	return (false);
}

// *	LEXER + PARSING -> true = success / false = error
bool tokenize_and_parse(t_data *data)
{
	if (data->user_input[0])
		add_history(data->user_input);
	if (!handle_spaces(&(data->user_input)))
		return (false);
	// ?	Tokenize the user_input and store it in data->token
	if (!tokenize_input(data, data->user_input))
		return (false);
	// ?	Check if the token list is empty (END_STR) and return false if it is
	if (data->token->type == END_STR)
		return (false);
	// *	DEBUG : Print the current token list
	print_token(data->token);
	// ?	Parse the token list to extract commands and arguments
	get_commands(data, data->token);
	return (true);
}