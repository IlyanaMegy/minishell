/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:35:11 by ilymegy           #+#    #+#             */
/*   Updated: 2023/12/27 23:34:02 by ilymegy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# define ADD 1
# define RM 2
# define GET 3

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
typedef struct s_env
{
	char			*name;
	char			*content;
	int				print_it;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

//  --------------------------------------------------------------------------------
// |								MINISHELL										|
//  --------------------------------------------------------------------------------

typedef struct s_minishell
{
}					t_minishell;

//  --------------------------------------------------------------------------------
// |								BUILTINS										|
//  --------------------------------------------------------------------------------

// builtins/env.c
void				ft_env(void);
t_env				*create_var(char *name, char *content, int print_it);
int					add_var_to_env(char *name, char *content, int print_it);
int					get_env(char **arg_env);

// builtins/export.c
int					ft_export(char **av);
int					check_var_name(char *arg, int *append);
void				display_export(void);

// builtins/export_utils.c
void				replace_var_in_env(char *name, char *content, int *append);
char				*get_var_content_from_env(char *var_name);
int					var_is_in_env(char *var_name);
t_env				*get_sorted_env(t_env **head);

// builtins/unset.c
int					ft_unset(char **args);

// builtins/cd.c
int					ft_cd(char **cmd);

// builtins/pwd.c
int					ft_pwd(void);

// builtins/echo.c
int					ft_echo(char **args);
//  --------------------------------------------------------------------------------
// |									CLEAN										|
//  --------------------------------------------------------------------------------

// clean/clean_it.c
t_env				*clean_env(t_env *e);
void				free_tab(char **map);

//  --------------------------------------------------------------------------------
// |								ERROR_HANDLER									|
//  --------------------------------------------------------------------------------
void				err_handler(int err, char *s);
char				*complexe_err_msg(int err, char *cmd);

//  --------------------------------------------------------------------------------
// |								EXECUTION										|
//  --------------------------------------------------------------------------------

// exec/exec_builtin.c

int					is_builtin(char *arg);
int					exec_builtin(char **args);

//  --------------------------------------------------------------------------------
// |									UTILS										|
//  --------------------------------------------------------------------------------

// utils/lst_functions.c
int					ms_lstsize(t_env *lst);

// utils/singletons.c
t_env				*single_env(t_env *env, int mode);
int					single_exit_s(int exit_s, int mode);
t_env				*copy_my_lst(t_env *src);

//  --------------------------------------------------------------------------------
// |									PARSING										|
//  --------------------------------------------------------------------------------

// parsing/parse.c
void				new_command(char *line);
#endif