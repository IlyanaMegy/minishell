/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:29:09 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/15 10:36:31 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   let's execute the given builtin
 * @param  data: t_data linked list
 * @param  cmd: current builtin to execute
 * @retval exit status
*/
int	exec_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->expanded_args[0], "echo") == 0)
		return (ft_echo(cmd->expanded_args));
	if (ft_strcmp(cmd->expanded_args[0], "cd") == 0)
		return (ft_cd(cmd->expanded_args));
	if (ft_strcmp(cmd->expanded_args[0], "env") == 0)
		return (ft_env(), 0);
	if (ft_strcmp(cmd->expanded_args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->expanded_args[0], "export") == 0)
		return (ft_export(cmd->expanded_args));
	if (ft_strcmp(cmd->expanded_args[0], "unset") == 0)
		return (ft_unset(cmd->expanded_args));
	return (ft_exit(data, cmd), single_exit_s(0, GET));
}

/**
 * @note   check if the command is a builtin or not
 * @param  arg: the given command to check
 * @retval 1 is yes, 0 is no
*/
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
