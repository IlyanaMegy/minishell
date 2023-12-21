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

/**
 * @brief  char *name, char *content, int print_it, t_env_var *next
 * @note   return var name, var content, do print it ?, next var
*/
typedef struct s_env_var
{
	char				*name;
	char				*content;
	int					print_it;
	struct s_env_var	*next;
}						t_env_var;

/**
 * @brief  t_env_var *first_var
 * @note   t_env *env is a pointer to the first element of env
*/
typedef struct s_env
{
	t_env_var			*f_var;
}						t_env;

//  --------------------------------------------------------------------------------
// |								MINISHELL										|
//  --------------------------------------------------------------------------------

typedef struct s_minishell
{
}						t_minishell;

extern t_minishell		g_minishell;

//  --------------------------------------------------------------------------------
// |								BUILTINS										|
//  --------------------------------------------------------------------------------

// builtins/env.c
void					ft_env(t_env *env);
void					add_var_to_env(t_env *env, char *name, char *content,
							int print_it);
void					get_env(char **arg_env, t_env *env);

// builtins/export.c
int						ft_export(t_env *env, char **av);
void					display_export(t_env *env);

// builtins/export_utils.c
int						print_export_err_msg(char *arg);
void					replace_var_in_env(t_env *env, char *name,
							char *content, int *append);
int						var_is_in_env(t_env *env, char *var_name);
void					get_sorted_env(t_env_var **head);
#endif