/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:50:50 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/26 19:50:53 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   get only two first characters of cmd
 * @param  cmd: given command
 * @retval two first char
*/
char	*two_first_char(char *cmd)
{
	char	*opt;

	opt = malloc(sizeof(char) * 3);
	opt[0] = cmd[0];
	opt[1] = cmd[1];
	opt[2] = '\0';
	return (opt);
}

/**
 * @note   display chdir/getcwd error
 * @param  builtin: 1 is cd, 2 is pwd
 * @retval None
*/
void	cdpwd_error_chdir_getcwd(int builtin)
{
	if (builtin == 1)
		ft_putstr_fd("chdir: error retrieving current directory: ",
			STDERR_FILENO);
	else
		ft_putstr_fd("pwd: error retrieving current directory: ",
			STDERR_FILENO);
	ft_putstr_fd("getcwd: cannot access parent directories: ",
		STDERR_FILENO);
	ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
}
