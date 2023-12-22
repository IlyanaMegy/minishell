/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:57:24 by ilymegy           #+#    #+#             */
/*   Updated: 2023/10/24 11:57:26 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	open_it(int ac, char **av)
{
	int	fd_in;

	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
			exit_handler("__ERROR_ARGS__:\nInvalid number of args.\n");
		here_doc(av);
		return (3);
	}
	else
	{
		fd_in = open_file(av[1], 0);
		if (dup2(fd_in, 0) == -1)
			exit_handler("__ERROR_PIPE__:\nError pipe.\n");
		close(fd_in);
		return (2);
	}
}

void	close_it(int ac, char **av)
{
	int	fd_out;

	if (ft_strcmp(av[1], "here_doc") == 0)
		fd_out = open_file(av[ac - 1], 2);
	else
		fd_out = open_file(av[ac - 1], 1);
	if (dup2(fd_out, 1) == -1)
		exit_handler("__ERROR_PIPE__:\nError pipe.\n");
	if (fd_out != -1)
		close(fd_out);
}
