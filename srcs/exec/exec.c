/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:22:24 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/13 16:22:25 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	executie(t_cmd *cmd_lst, int fds[6])
{
	char **cmds_tab;

	cmds_tab = get_cmds_from_cmd_lst();
	if (is_builtin(cmds_tab[0]) && !fds[5])
	{
		close (fds[2]);
		close(fds[3]);
		single_exit_s(exec_builtin(cmds_tab), ADD);
		return;
	}
}
