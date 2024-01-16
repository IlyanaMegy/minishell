/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:44:39 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/16 14:22:41 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	handle_input(t_cmd **last_cmd, t_token **token_lst)
{
	t_token		*token;
	t_cmd		*cmd;

	token = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	if (!init_io_cmd(&cmd))
		return (false);
	cmd->io_list->path = ft_strdup(token->next->value);
	cmd->io_list->type = IO_IN;
	token = token->next;
	*token_lst = token;
	return (true);
}
