/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:43:54 by ilymegy           #+#    #+#             */
/*   Updated: 2023/10/10 17:43:56 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	exit_handler(char *msg);
void	ft_free_tab(char **tab);
void	swap_pipes(int fd[3]);
void	ft_close_all(int fd[3]);
void	ft_dup2(int fdin, int fdout);
void	open_it(int ac, char **av, int *fd);
void	close_it(int ac, char **av, int *fd);
void	exec(char *cmd, char **env);
void	here_doc_put_in(char **av, int *fd);
#endif