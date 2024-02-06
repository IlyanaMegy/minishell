#include "../../inc/minishell.h"

static size_t	unquoted_strlen(char *str)
{
	size_t	i;
	size_t	len;
	char	quotes;

	i = 0;
	len = 0;
	quotes = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && str[i + 1])
		{
			if (!quotes)
				quotes = str[i++];
			else if (str[i] == quotes)
				quotes = ((i++) && 0);
			else
				len += (i++ || 1);
		}
		else
			len += (i++ || 1);
	}
	return (len);
}

static void	unquote_fill_it(char *str, size_t *i, char *res, size_t *j)
{
	char	quotes;

	quotes = str[(*i)++];
	while (str[*i] != quotes)
		res[(*j)++] = str[(*i)++];
	(*i)++;
}

char	*strip_quotes(char *str)
{
	char *res;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	res = ft_calloc(1 + unquoted_strlen(str), sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && str[(i + 1)])
			(unquote_fill_it(str, &i, res, &j));
		else
			res[j++] = str[i++];
	}
	return (free(str), res);
}