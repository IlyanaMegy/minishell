/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:44:39 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/18 10:51:48 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	handle_input_trunc(t_cmd **last_cmd,
	t_token **token_lst, t_token_type type)
{
	t_token		*token;
	t_cmd		*cmd;

	token = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	if (!init_io_cmd(&cmd))
		return (false);
	if (type == TRUNC && cmd->io_list->path)
		free_ptr(cmd->io_list->path);
	cmd->io_list->path = ft_strdup(token->next->value);
	if (!cmd->io_list->path)
		return (false);
	if (type == INPUT)
		cmd->io_list->type = IO_IN;
	else if (type == TRUNC)
		cmd->io_list->type = IO_OUT;
	if (token->next->next
		&& (token->next->next->type == WORD || token->next->next->type == PIPE))
		token = token->next->next;
	else
		token = token->next;
	*token_lst = token;
	return (true);
}
