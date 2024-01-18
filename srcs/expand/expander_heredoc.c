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
 * @note   translate and write in fd
 * @param  str: given line
 * @param  i: index
 * @param  fd: file descriptor
 * @retval index
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
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += heredoc_expander_w(str, i, fd);
		else
			i += (ft_putchar_fd(str[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}
