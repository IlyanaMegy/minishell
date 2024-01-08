// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   utils.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/10/24 11:57:24 by ilymegy           #+#    #+#             */
// /*   Updated: 2023/10/24 11:57:26 by ilymegy          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/pipex.h"

// int	open_file(char *file, int in_or_out)
// {
// 	int	ret;

// 	if (in_or_out == 0)
// 		ret = open(file, O_RDONLY, 0777);
// 	if (in_or_out == 1)
// 		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (in_or_out == 2)
// 		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	if (ret == -1)
// 		exit_handler("__ERROR_FILE__:\nCan't read outfile or infile.\n");
// 	return (ret);
// }

// void	open_it(int ac, char **av, int *fd)
// {
// 	int	fdi;

// 	if (ft_strcmp(av[1], "here_doc") == 0)
// 	{
// 		if (ac < 6)
// 			exit_handler("__ERROR_ARGS__:\nInvalid number of args.\n");
// 		here_doc_put_in(av, fd);
// 	}
// 	else
// 	{
// 		fdi = open_file(av[1], 0);
// 		ft_dup2(fdi, fd[1]);
// 		close(fdi);
// 	}
// }

// void	close_it(int ac, char **av, int *fd)
// {
// 	int	fdo;

// 	if (ft_strcmp(av[1], "here_doc") == 0)
// 		fdo = open_file(av[ac - 1], 2);
// 	else
// 		fdo = open_file(av[ac - 1], 1);
// 	ft_dup2(fd[2], fdo);
// 	close(fdo);
// }
