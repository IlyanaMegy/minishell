/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:29:09 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/04 16:29:11 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_builtin(t_data *data)
{
	if (ft_strcmp(data->cmd->args[0], "echo") == 0)
		return (ft_echo(data->cmd->args));
	if (ft_strcmp(data->cmd->args[0], "cd") == 0)
		return (ft_cd(data->cmd->args));
	if (ft_strcmp(data->cmd->args[0], "env") == 0)
		return (ft_env(), 0);
	if (ft_strcmp(data->cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(data->cmd->args[0], "export") == 0)
		return (ft_export(data->cmd->args));
	if (ft_strcmp(data->cmd->args[0], "unset") == 0)
		return (ft_unset(data->cmd->args));
	ft_exit(data);
	return (0);
}

int	is_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strcmp(arg, "echo")
		|| !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "exit")
		|| !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env"))
		return (1);
	return (0);
}
