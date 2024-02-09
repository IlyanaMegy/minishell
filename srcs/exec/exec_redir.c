/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:32:36 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/17 14:36:15 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @note   can we write in file ?
 * @param  file: the file in question
 * @retval exit status
*/
int	check_write(char *file)
{
	if (!*file)
		return (err_handler(ERR_NOFILEDIR, file), 1);
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return (err_handler(ERR_PERM_DENIED, file), 1);
		return (ENO_SUCCESS);
	}
	return (err_handler(ERR_NOFILEDIR, file), ENO_NOT_FOUND);
}

/**
 * @note   can we read file ?
 * @param  file: the file in question
 * @retval exit status
*/
int	check_read(char *file)
{
	if (!*file)
		return (err_handler(ERR_NOFILEDIR, file), 1);
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			return (err_handler(ERR_PERM_DENIED, file), 1);
		return (ENO_SUCCESS);
	}
	return (err_handler(ERR_NOFILEDIR, file), ENO_NOT_FOUND);
}

/**
 * @note   opening after checking infile
 * @param  io_lst: in and out files data list
 * @param  status: exit status
 * @retval exit status
*/
int	open_in(t_io_cmd *io_lst, int *status)
{
	int	fdi;

	if (!io_lst->expanded_value || io_lst->expanded_value[1])
	{
		err_handler(ERR_AMBIG_REDIR, io_lst->path);
		*status = 1;
		return (*status);
	}
	fdi = open(io_lst->expanded_value[0], O_RDONLY);
	if (fdi == -1)
	{
		*status = check_read(io_lst->expanded_value[0]);
		return (*status);
	}
	dup2(fdi, STDIN_FILENO);
	close(fdi);
	*status = 0;
	return (*status);
}

/**
 * @note   opening after checking outfile
 * @param  io_lst: in and out files data list
 * @param  status: exit status
 * @retval exit status
*/
int	open_out(t_io_cmd *io_lst, int *status)
{
	int	fdo;

	if (!io_lst->expanded_value || io_lst->expanded_value[1])
	{
		err_handler(ERR_AMBIG_REDIR, io_lst->path);
		*status = 1;
		return (*status);
	}
	fdo = open(io_lst->expanded_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fdo == -1)
	{
		*status = check_write(io_lst->expanded_value[0]);
		return (*status);
	}
	dup2(fdo, STDOUT_FILENO);
	close(fdo);
	*status = 0;
	return (*status);
}

/**
 * @note   opening on append after checking outfile
 * @param  io_lst: in and out files data list
 * @param  status: exit status
 * @retval exit status
*/
int	open_append(t_io_cmd *io_lst, int *status)
{
	int	fdo;

	if (!io_lst->expanded_value || io_lst->expanded_value[1])
	{
		err_handler(ERR_AMBIG_REDIR, io_lst->path);
		*status = 1;
		return (*status);
	}
	fdo = open(io_lst->expanded_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fdo == -1)
	{
		*status = check_write(io_lst->expanded_value[0]);
		return (*status);
	}
	dup2(fdo, STDOUT_FILENO);
	close(fdo);
	*status = 0;
	return (*status);
}
