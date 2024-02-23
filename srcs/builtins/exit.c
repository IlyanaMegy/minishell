/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:21:14 by ilymegy           #+#    #+#             */
/*   Updated: 2024/02/17 21:52:33 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   skip thes spaces and find the sign if there is one
 * @param  number: given exit_status arg
 * @param  *i: index
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
 * @note   clean and exit exit builtin
 * @param  data: t_data structure
 * @param  exit_status: exit status
 * @param  err_state: error state
 * @param  msg: error message
 * @retval None
 */
void	clean_exit_exit(t_data *data, int exit_status, int err_state, char *msg)
{
	int	exit_s;

	exit_s = single_exit_s(exit_status, ADD);
	err_handler(err_state, msg);
	clean_program(data);
	exit(exit_s);
}

/**
 * @note   verify is correct number, find sign, convert to int
 * @param  data: t_data structure
 * @param  number: given exit_status arg
 * @retval 255 if not int number and exit, int number is good exit status
 */
int	calcul_exit_status(t_data *data, char *number)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	skip_spaces_get_sign(number, &i, &sign);
	if (!ft_isnumber(number + i))
		clean_exit_exit(data, 2, ERR_EXIT_NB, number);
	res = 0;
	while (number[i])
	{
		res = (res * 10) + (number[i] - '0');
		if (sign == -1 && res - 1 == LONG_MAX && !number[i + 1])
			res = 0;
		if (res > LONG_MAX)
			clean_exit_exit(data, 2, ERR_EXIT_NB, number);
		i++;
	}
	return ((res * sign) % 256);
}

/**
 * @note   nicely exit the program minishell
 * @param  data: t_data structure
 * @param  cmd : current command
 * @retval None
 */
void	ft_exit(t_data *data, t_cmd *cmd)
{
	if (!cmd->prev && !cmd->next)
		ft_putstr_fd("exit\n", 1);
	if (cmd->expanded_args[1])
	{
		if (cmd->expanded_args[2] && ft_isnumber(cmd->expanded_args[1]))
		{
			single_exit_s(1, ADD);
			err_handler(ERR_ARGS, "exit");
			return ;
		}
		else
			single_exit_s(calcul_exit_status(data, cmd->expanded_args[1]), ADD);
	}
	clean_program(data);
	exit(single_exit_s(0, GET));
}
