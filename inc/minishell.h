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

# define ERR_ARGS 2
# define ERR_PATH 3
# define ERR_NOFILEDIR 4
# define ERR_EXPORT 5
# define ERR_UNSET 6

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
	struct s_env_var	*prev;
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
int						add_var_to_env(t_env *env, char *name, char *content,
							int print_it);
int						get_env(char **arg_env, t_env *env);

// builtins/export.c
int						ft_export(t_env *env, char **av);
int						check_var_name(char *arg, int *append);
void					display_export(t_env *env);

// builtins/export_utils.c
int						print_export_err_msg(char *arg);
void					replace_var_in_env(t_env *env, char *name,
							char *content, int *append);
char					*get_var_content_from_env(t_env *env, char *var_name);
int						var_is_in_env(t_env *env, char *var_name);
void					get_sorted_env(t_env_var **head);

// builtins/unset.c
int						ft_unset(t_env *env, char **args);

// builtins/cd.c
int						ft_cd(t_env *env, char **cmd);

//builtins/pwd.c
int						ft_pwd(void);
//  --------------------------------------------------------------------------------
// |									CLEAN										|
//  --------------------------------------------------------------------------------

// clean/clean_it.c
void					clean_env(t_env *env);

//  --------------------------------------------------------------------------------
// |								ERROR_HANDLER									|
//  --------------------------------------------------------------------------------
void					err_handler(int err, char *s);
char					*complexe_err_msg(int err, char *cmd);
#endif