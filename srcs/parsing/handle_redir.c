/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:44:39 by ltorkia           #+#    #+#             */
/*   Updated: 2024/01/18 14:19:36 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*generate_name(void)
{
	static int	i = 0;
	char		*n;
	char		*name;

	n = ft_itoa(i);
	name = ft_strjoin(HEREDOC_NAME, n);
	if (!name)
		return (NULL);
	free_ptr(&n);
	i++;
	return (name);
}

static void	set_io_type(t_io_cmd **io_list, t_token_type type)
{
	if (type == INPUT)
		(*io_list)->type = IO_IN;
	else if (type == TRUNC)
		(*io_list)->type = IO_OUT;
	else if (type == HEREDOC)
		(*io_list)->type = IO_HEREDOC;
	else if (type == APPEND)
		(*io_list)->type = IO_APPEND;
}

static void	set_io_path(t_io_cmd **io_list, t_token **token, t_token_type type)
{
	if (type == HEREDOC)
		(*io_list)->path = generate_name();
	else
		(*io_list)->path = ft_strdup((*token)->next->value);
}

bool	handle_redir(t_cmd **last_cmd, t_token **token_lst, t_token_type type)
{
	t_token		*token;
	t_cmd		*cmd;

	token = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	if (!init_io_cmd(&cmd))
		return (false);
	set_io_path(&cmd->io_list, &token, type);
	if (!cmd->io_list->path)
		return (false);
	set_io_type(&cmd->io_list, type);
	if (token->next->next
		&& (token->next->next->type == WORD
			|| token->next->next->type == PIPE))
		token = token->next->next;
	else
		token = token->next;
	*token_lst = token;
	return (true);
}
