/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:21:14 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/13 16:21:16 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   skip thes spaces and find the sign if there is one
 * @param  number: given exit_status arg
 * @param  i: index
 * @param  sign: well is a sign
 * @retval None
*/
void	skip_spaces_get_sign(char *number, int *i, int *sign)
{
	while (number[*i] && number[*i] == ' ')
		(*i)++;
	if (number[*i] == '+' || number[*i] == '-')
	{
		if (number[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

/**
 * @note   nicely exit the program after all cleaned up
 * @param  number: given exit_status
 * @param  args: exit cmd and exit status numbers
 * @retval None
*/
void	clean_exit_exit(int exit_status, int err_state, char *msg, char **args)
{
	int	exit_s;

	exit_s = single_exit_s(exit_status, ADD);
	err_handler(err_state, msg);
	clean_program(args);
	exit(exit_s);
}

/**
 * @note   verify is correct number, find sign, convert to int 
 * @param  number: given exit_status arg
 * @param  args: exit cmd and exit status numbers
 * @retval 255 if not int number and exit, int number is good exit status
*/
int	calcul_exit_status(char *number, char **args)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	skip_spaces_get_sign(number, &i, &sign);
	if (!ft_isnumber(number + i))
		clean_exit_exit(255, ERR_EXIT_NB, number, args);
	res = 0;
	while (number[i])
	{
		res = (res * 10) + (number[i] - '0');
		if (res > LONG_MAX)
			clean_exit_exit(255, ERR_EXIT_NB, number, args);
		i++;
	}
	return ((res * sign) % 256);
}

/**
 * @note   nicely exit the program minishell
 * @param  args: exit cmd and exit status numbers
 * @retval None
*/
void	ft_exit(char **args)
{
	int	exit_s;

	exit_s = single_exit_s(0, GET);
	if (args[1])
	{
		if (args[2] && ft_isnumber(args[1]))
			clean_exit_exit(1, ERR_ARGS, "exit", args);
		else
			exit_s = single_exit_s(calcul_exit_status(args[1], args), ADD);
	}
	clean_program(args);
	exit(single_exit_s(0, GET));
}
