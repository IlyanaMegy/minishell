/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:32:36 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/11 16:32:37 by ilymegy          ###   ########.fr       */
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

	if (!io_lst->path)
	{
		err_handler(ERR_AMBIG_REDIR, io_lst->path);
		*status = 1;
		return (*status);
	}
	fdi = open(io_lst->path, O_RDONLY);
	if (fdi == -1)
	{
		*status = check_read(io_lst->path);
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

	if (!io_lst->path)
	{
		err_handler(ERR_AMBIG_REDIR, io_lst->path);
		*status = 1;
		return (*status);
	}
	fdo = open(io_lst->path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fdo == -1)
	{
		*status = check_write(io_lst->path);
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
int	open_out(t_io_cmd *io_lst, int *status)
{
	int	fdo;

	if (!io_lst->path)
	{
		err_handler(ERR_AMBIG_REDIR, io_lst->path);
		*status = 1;
		return (*status);
	}
	fdo = open(io_lst->path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fdo == -1)
	{
		*status = check_write(io_lst->path);
		return (*status);
	}
	dup2(fdo, STDOUT_FILENO);
	close(fdo);
	*status = 0;
	return (*status);
}
