#include "../../inc/minishell.h"

static	void	skip_word(char const *s, size_t	*i)
{
	char	quotes;

	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		else
		{
			quotes = s[(*i)++];
			while (s[(*i)] != quotes)
				(*i)++;
			(*i)++;
		}
	}
}

static char	**allocate_size(char const *s, char **strs)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			start = i;
			skip_word(s, &i);
			strs[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!strs[j])
				return (NULL);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

static void	gimme_that(const char *s, char **strs, size_t *i, size_t j)
{
	char	quotes;
	size_t	k;

	k = 0;
	while (s[(*i)] && s[(*i)] != ' ')
	{
		if (s[(*i)] != '\'' && s[(*i)] != '"')
			strs[j][k++] = s[(*i)++];
		else
		{
			quotes = s[(*i)++];
			strs[j][k++] = quotes;
			while (s[(*i)] != quotes)
				strs[j][k++] = s[(*i)++];
			strs[j][k++] = s[(*i)++];
		}
	}
}

static char	**fill_it(char const *s, char **strs)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && strs[j])
	{
		if (s[i] != ' ')
		{
			gimme_that(s, strs, &i, j);
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (strs);
}

char	**expander_split(char const *s)
{
	size_t		count;
	char		**strs;
	char		**free_me;
	size_t		i;

	if (!s)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && ++count)
			skip_word(s, &i);
		while (s[i] && s[i] == ' ')
			i++;
	}
	strs = ft_calloc(count + 1, sizeof(char *));
	free_me = strs;
	strs = allocate_size(s, strs);
	if (!strs || !count)
		return (free_tab(free_me), NULL);
	return (fill_it(s, strs));
}