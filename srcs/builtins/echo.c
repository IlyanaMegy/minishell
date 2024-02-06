/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:20:31 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/25 11:20:02 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_alone_word(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] == ' ')
		i++;
	while (arg[i] && arg[i] != ' ')
		i++;
	while (arg[i] && arg[i] == ' ')
		i++;
	if (arg[i] != '\0')
		return (0);
	return (1);
}

/**
 * @note   check if there's a -n option for echo builtin
 * @param  s: option
 * @retval 1 all is good, 0 not an option
*/
int	check_option(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	skip_spaces(char *arg, char *next)
{
	int	j;

	j = 0;
	while (arg[j] && arg[j] == ' ')
		j++;
	while (arg[j] && arg[j] != ' ')
	{
		ft_putchar_fd(arg[j], 1);
		j++;
	}
	if (next && ft_strcmp(next, " "))
		ft_putstr_fd(" ", 1);
}

int	just_an_opt(char *arg, int *opt)
{
	int	i;

	i = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] && arg[i - 1] != 'n')
		return (0);
	while (arg[i] && arg[i] == ' ')
		i++;
	if (arg[i])
		return (0);
	*opt = 1;
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	opt;

	i = 1;
	opt = 0;
	// if (just_an_opt(args[i], &opt))
	// 	i++;
	while (args[i] != NULL && check_option(args[i]))
	{
		opt = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		// if (is_alone_word(args[i]))
		// 	skip_spaces(args[i], args[i + 1]);
		// else
		// {
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		// }
		i++;
	}
	if (opt == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
