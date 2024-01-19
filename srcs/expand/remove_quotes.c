/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:47:54 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/20 00:10:46 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_new_len(char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(arg);
	while (arg[i])
	{
		if (is_quote(arg, i))
			len--;
		i++;
	}
	return (len);
}

static char	*get_clean_arg(char *arg)
{
	int		i;
	int		j;
	int		len;
	char 	*new_arg;

	len = get_new_len(arg);
	new_arg = malloc(sizeof(char) * len + 1);
	i = 0;
	j = 0;
	len = ft_strlen(arg);
	while (arg[i])
	{
		if (!is_quote(arg, i))
		{
			new_arg[j] = arg[i];
			j++;
		}
		i++;
	}
	new_arg[j] = '\0';
	return (new_arg);
}

void	remove_quotes(t_cmd	**cmd)
{
	t_cmd	*temp;
	int		i;

	temp = *cmd;
	i = 0;
	while (*cmd)
	{
		while ((*cmd)->expanded_args[i])
		{
			(*cmd)->expanded_args[i] = get_clean_arg((*cmd)->expanded_args[i]);
			if (!(*cmd)->expanded_args[i])
				return ;
			i++;
		}
		(*cmd) = (*cmd)->next;
	}
	*cmd = temp;
}