// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/10/10 17:42:51 by ilymegy           #+#    #+#             */
// /*   Updated: 2023/10/10 17:42:53 by ilymegy          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/pipex.h"

// void	here_doc_put_in(char **av, int *fd)
// {
// 	char	*ret;
// 	t_gnl	*clear;

// 	while (1)
// 	{
// 		clear = malloc(sizeof(t_gnl));
// 		if (!clear)
// 			return ;
// 		ret = get_next_line(0, 0, &clear);
// 		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
// 		{
// 			free(ret);
// 			free(clear->content);
// 			free(clear);
// 			exit(0);
// 		}
// 		ft_putstr_fd(ret, fd[1]);
// 		free(ret);
// 	}
// 	if (dup2(fd[0], 0) == -1)
// 		exit_handler("__ERROR_PIPE__:\nError pipe.\n");
// 	close(fd[0]);
// }

// void	do_pipe(char **av, int *i, int *fd, char **env)
// {
// 	pid_t	pid[4096];

// 	if (pipe(fd) < 0)
// 		exit_handler("__ERROR_PIPE__:\nError pipe.\n");
// 	pid[i[0]] = fork();
// 	if (pid[i[0]] < 0)
// 		exit_handler("__ERROR_FORK__:\nError fork.\n");
// 	if (!pid[i[0]])
// 	{
// 		if (i[0] == 0)
// 			open_it(i[1], av, fd);
// 		else if (i[0] == i[1] - 4)
// 			close_it(i[1], av, fd);
// 		else
// 			ft_dup2(fd[2], fd[1]);
// 		ft_close_all(fd);
// 		exec(av[i[0] + 2], env);
// 	}
// 	if (!ft_strcmp(av[1], "here_doc"))
// 		wait(0);
// }

// int	main(int ac, char **av, char **env)
// {
// 	pid_t	pid[4096];
// 	int		i[3];
// 	int		fd[3];

// 	if (ac < 5)
// 		exit_handler("__ERROR_ARGS__:\nInvalid number of args.\n");
// 	i[0] = -1;
// 	i[1] = ac;
// 	fd[2] = dup(STDIN_FILENO);
// 	while (++i[0] < ac - 3)
// 	{
// 		do_pipe(av, i, fd, env);
// 		swap_pipes(fd);
// 	}
// 	close(fd[2]);
// 	i[0] = -1;
// 	while (++i[0] < ac - 3)
// 		waitpid(pid[i[0]], &i[2], 0);
// 	return (0);
// }
