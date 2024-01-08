// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execute.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/11/17 12:02:43 by ilymegy           #+#    #+#             */
// /*   Updated: 2023/11/17 12:02:50 by ilymegy          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/pipex.h"

// char	*my_getenv(char *name, char **env)
// {
// 	int		i;
// 	int		j;
// 	char	*sub;

// 	i = 0;
// 	while (env[i])
// 	{
// 		j = 0;
// 		while (env[i][j] && env[i][j] != '=')
// 			j++;
// 		sub = ft_substr(env[i], 0, j);
// 		if (ft_strcmp(sub, name) == 0)
// 		{
// 			free(sub);
// 			return (env[i] + j + 1);
// 		}
// 		free(sub);
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*get_path(char *cmd, char **env)
// {
// 	int		i;
// 	char	*exec;
// 	char	**allpath;
// 	char	*path_part;
// 	char	**s_cmd;

// 	i = -1;
// 	allpath = ft_split(my_getenv("PATH", env), ':');
// 	s_cmd = ft_split(cmd, ' ');
// 	while (allpath[++i])
// 	{
// 		path_part = ft_strjoin(allpath[i], "/");
// 		exec = ft_strjoin(path_part, s_cmd[0]);
// 		free(path_part);
// 		if (access(exec, F_OK | X_OK) == 0)
// 		{
// 			ft_free_tab(allpath);
// 			ft_free_tab(s_cmd);
// 			return (exec);
// 		}
// 		free(exec);
// 	}
// 	ft_free_tab(allpath);
// 	ft_free_tab(s_cmd);
// 	return (cmd);
// }

// void	exec(char *cmd, char **env)
// {
// 	char	**s_cmd;
// 	char	*path;

// 	s_cmd = ft_split(cmd, ' ');
// 	path = get_path(s_cmd[0], env);
// 	if (execve(path, s_cmd, env) == -1)
// 	{
// 		ft_putstr_fd("Pipex: command not found: ", 2);
// 		ft_putendl_fd(s_cmd[0], 2);
// 		ft_free_tab(s_cmd);
// 		exit(127);
// 	}
// }
