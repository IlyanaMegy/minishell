/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:29:30 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/25 21:23:06 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   handling errors prints
 * @param  err: error code
 * @param  s: wrong argument or action
 * @retval None
*/
void	err_handler(int err, char *s)
{
	char	*start_msg;
	char	*err_msg;
	char	*all_msg;

	start_msg = ft_strdup("minishell: ");
	err_msg = NULL;
	if (err == ERR_ARGS)
		err_msg = ft_strjoin(s, ": too many arguments\n");
	else if (err == ERR_EXPORT || err == ERR_EXPORT_OPT || err == ERR_UNSET
		|| err == ERR_UNSET_OPT || err == ERR_EXIT_NB)
		err_msg = complexe_err_msg(err, s);
	else if (err == ERR_PATH)
		err_msg = ft_strjoin(s, ": HOME not set\n");
	else if (err == ERR_NOCMD)
		err_msg = ft_strjoin(s, ": command not found\n");
	else if (err == ERR_NOFILEDIR)
		err_msg = ft_strjoin(s, ": No such file or directory\n");
	else if (err == ERR_PERM_DENIED)
		err_msg = ft_strjoin(s, ": Permission denied\n");
	else if (err == ERR_AMBIG_REDIR)
		err_msg = ft_strjoin(s, ": ambiguous redirect\n");
	all_msg = ft_strjoin(start_msg, err_msg);
	ft_putstr_fd(all_msg, STDERR_FILENO);
	(free(start_msg), free(err_msg), free(all_msg));
}

/**
 * @note   handle join of complexe errors
 * @param  err: error code
 * @param  cmd: wrong argument
 * @retval return joined message
*/
char	*complexe_err_msg(int err, char *cmd)
{
	char	*tmp;
	char	*res;
	char	*opt;

	tmp = NULL;
	res = NULL;
	opt = two_first_char(cmd);
	if (err == ERR_EXPORT || err == ERR_UNSET || err == ERR_EXPORT_OPT
		|| err == ERR_UNSET_OPT)
	{
		if (err == ERR_EXPORT || err == ERR_UNSET)
			tmp = ft_strjoin(cmd, "\': not a valid identifier\n");
		else if (err == ERR_EXPORT_OPT || err == ERR_UNSET_OPT)
			tmp = ft_strjoin(opt, "\': invalid option\n");
		if (err == ERR_EXPORT || err == ERR_EXPORT_OPT)
			res = ft_strjoin("export: `", tmp);
		else if (err == ERR_UNSET || err == ERR_UNSET_OPT)
			res = ft_strjoin("unset: `", tmp);
	}
	else if (err == ERR_EXIT_NB)
	{
		tmp = ft_strjoin(cmd, ": numeric argument required\n");
		res = ft_strjoin("exit: ", tmp);
	}
	return (free(tmp), free(opt), res);
}
