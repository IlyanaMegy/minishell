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

#include "../../inc/pipex.h"

void	exit_handler(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	swap_pipes(int fd[3])
{
	dup2(fd[0], fd[2]);
	close(fd[0]);
	close(fd[1]);
}

void	ft_close_all(int fd[3])
{
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

void	ft_dup2(int fdin, int fdout)
{
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
}
