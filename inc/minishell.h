/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:35:11 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/13 16:35:12 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"

//  --------------------------------------------------------------------------------
// |									ENV											|
//  --------------------------------------------------------------------------------
typedef struct s_exp_env_var
{
	char			*name;
	char			*content;
	int				print_it;
	t_exp_env_var	*next;
}					t_exp_env_var;

typedef struct s_exp_env
{
	t_exp_env_var	*f_var;
}					t_exp_env;

typedef struct s_env_var
{
	char			*name;
	char			*content;
	t_env_var		*next;
}					t_env_var;

typedef struct s_env
{
	t_env_var		*f_var;
}					t_env;

//  --------------------------------------------------------------------------------
// |								MINISHELL										|
//  --------------------------------------------------------------------------------

typedef struct s_minishell
{
}					t_minishell;

extern t_minishell	g_minishell;

#endif