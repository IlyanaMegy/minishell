/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:59:07 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/30 13:42:52 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   update or return current heredoc_sigint status
 * @param  sign_child_s: heredoc_sigint status
 * @param  mode: ADD or GET
 * @retval return current heredoc_sigint status
*/
bool	single_heredoc_sigint(bool heredoc_sigint_s, int mode)
{
	static bool	single_heredoc_sigint = 0;

	if (mode == ADD)
		single_heredoc_sigint = heredoc_sigint_s;
	if (mode == GET)
		return (single_heredoc_sigint);
	return (single_heredoc_sigint);
}

/**
 * @note   update or return current sigint_child status
 * @param  sign_child_s: sigint_child status
 * @param  mode: ADD or GET
 * @retval return current sigint_child status
*/
bool	single_sign_child(bool sign_child_s, int mode)
{
	static bool	single_sign_child = 0;

	if (mode == ADD)
		single_sign_child = sign_child_s;
	if (mode == GET)
		return (single_sign_child);
	return (single_sign_child);
}
