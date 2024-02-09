/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:52:24 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/18 16:52:26 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   reveal environment variable and write in fd
 * @param  str: given line
 * @param  i: current index
 * @param  fd: file descriptor
 * @retval current updated index
*/
static int	heredoc_expander_w(char *str, int i, int fd)
{
	int		start;
	char	*tmp1;
	char	*tmp2;

	start = ++i;
	if (str[i] == '?')
		return (ft_putnbr_fd(single_exit_s(0, GET), fd), 2);
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (i != start)
	{
		tmp1 = ft_substr(str, start, i);
		tmp2 = get_var_content_from_env(tmp1);
		free(tmp1);
		if (tmp2)
			ft_putstr_fd(tmp2, fd);
	}
	return (i);
}

/**
 * @note   handling here_doc expander
 * @param  str: given line
 * @param  fd: file descriptor where we write
 * @retval None
*/
void	heredoc_expander(char *str, int fd)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '$')
			i += heredoc_expander_w(str, i, fd);
		else
			i += (ft_putchar_fd(str[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}

/**
 * @note   remove quotes simple and double from delimiter
 * @param  res: delimiter string
 * @retval cleaned delimiter
*/
char	*cleaned_heredoc_delim(char *res)
{
	char	*cleaned;
	int		i;
	int		start;
	char	*sub;

	sub = NULL;
	i = 0;
	cleaned = ft_strdup("");
	while (res[i])
	{
		if (res[i] == '"' || res[i] == '\'')
			i++;
		start = i;
		while (res[i] && !(res[i] == '"' || res[i] == '\''))
			i++;
		sub = ft_substr(res, start, i - start);
		cleaned = strjoin_f(cleaned, sub);
	}
	return (free(res), cleaned);
}

/**
 * @note   handling dollar in heredoc delimiter
 * @param  path: delimiter
 * @param  *i: index
 * @retval keep the dollar or not
*/
char	*handle_dollar_delim(char *path, int *i)
{
	if ((path[*i + 1] == '"' || path[*i + 1] == '\''))
	{
		if (*i == 0)
		{
			(*i)++;
			return (ft_strdup(""));
		}
		else if (path[*i - 1] && path[*i - 1] != '$')
		{
			(*i)++;
			return (ft_strdup(""));
		}
	}
	(*i)++;
	return (ft_strdup("$"));
}

/**
 * @note   get expanded heredoc delimiter
 * @param  path: heredoc delimiter
 * @retval expanded heredoc delimiter
*/
char	*expand_heredoc_delim(char *path)
{
	char	*res;
	char	*sub;
	int		start;
	int		i;

	res = ft_strdup("");
	sub = NULL;
	i = 0;
	while (path[i])
	{
		if (path[i] == '$')
			res = strjoin_f(res, handle_dollar_delim(path, &i));
		start = i;
		while (path[i] && !(path[i] == '$'))
			i++;
		sub = ft_substr(path, start, i - start);
		res = strjoin_f(res, sub);
	}
	res = cleaned_heredoc_delim(res);
	return (res);
}
