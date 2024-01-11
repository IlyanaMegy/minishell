/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:35:11 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/08 14:26:10 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>

# define PROMPT "minishell$ "

# define ADD 1
# define RM 2
# define GET 3

# define ERR_ARGS 2
# define ERR_PATH 3
# define ERR_NOFILEDIR 4
# define ERR_EXPORT 5
# define ERR_UNSET 6
# define ERR_EXIT_NB 7

//  --------------------------------------------------------------------------------
// |							GLOBAL VARIABLE										|
//  --------------------------------------------------------------------------------

extern int			g_sig_exit;

//  --------------------------------------------------------------------------------
// |								ENV												|
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
// |								LEXER											|
//  --------------------------------------------------------------------------------

/**
 * @brief  char *value, int type, int quote_status, t_token *prev, t_token *next
 * @note   return var value, var type, var quote_status, prev var, next var
*/
typedef struct s_token
{
	char			*value;
	int				type;
	int				quote_status;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

//  --------------------------------------------------------------------------------
// |								PARSING											|
//  --------------------------------------------------------------------------------

/**
 * @note   
 * @example < file cat | grep "hello" | ls
 * @example	s_cmd *first_cmd : cmd=cat, file_out=NULL, args=cat-file, fd_in=1, fd_out=?, pipe_out=1.
 * @example	s_cmd *second_cmd : cmd=grep, file_out=NULL, args=grep-hello, fd_in=? ...
 * @brief  return char *cmd, char *path, char **args, int fd_in, int fd_out, bool pipe_out, t_cmd *prev, t_cmd *next
 * @note   return var cmd, var path, var args, var fd_in, var fd_out, var pipe_out, prev var, next var
*/
typedef struct s_cmd
{
	char			*cmd;
	char			*file_out;
	char			**args;
	int				fd_in;
	int				fd_out;
	bool			pipe_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

//  --------------------------------------------------------------------------------
// |							MAIN STRUCTURE										|
//  --------------------------------------------------------------------------------
/**
 * @brief  return char *user_input, t_token *token, t_cmd *cmd
 * @note   return var user_input, token var, cmd var
*/
typedef struct s_data
{
	char			*user_input;
	t_token			*token;
	t_cmd			*cmd;
}					t_data;

//  --------------------------------------------------------------------------------
// |								ENUMS											|
//  --------------------------------------------------------------------------------

enum				e_token_type
{
	WHITESPACE = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END_STR
};

enum				e_quote_status
{
	NONE,
	SINGLE,
	DOUBLE
};

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
int					replace_var_in_env(char *name, char *content, int *append);
char				*get_var_content_from_env(char *var_name);
t_env				*get_sorted_env(t_env **head);

// builtins/unset.c
int					ft_unset(char **args);
int					var_is_in_env(char *var_name);

// builtins/cd.c
int					ft_cd(char **cmd);

// builtins/pwd.c
int					ft_pwd(void);

// builtins/echo.c
int					ft_echo(char **args);

// builtins/exit.c
void				ft_exit(t_data *data);

//  --------------------------------------------------------------------------------
// |									CLEAN										|
//  --------------------------------------------------------------------------------

// clean/clean_it.c
t_env				*clean_env(t_env *e);
void				free_ptr(void *ptr);
void				free_tab(char **map);
void				free_data(t_data *data);
void				clean_program(t_data *data);

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
int					exec_builtin(t_data *data);

//  --------------------------------------------------------------------------------
// |									UTILS										|
//  --------------------------------------------------------------------------------

// utils/lst_manip.c
int					ms_lstsize(t_env *lst);
t_env				*copy_my_lst(t_env *src);
char				**env_to_tab(t_env *env_lst);
void				print_tab(char **tab);

// utils/singletons.c
t_env				*single_env(t_env *env, int mode);
int					single_exit_s(int exit_s, int mode);

// utils/signals.c
// void				init_signals(void);

//  --------------------------------------------------------------------------------
// |									LEXER										|
//  --------------------------------------------------------------------------------

// lexer/token.c
bool				tokenize_input(t_data *data, char *s);
int					save_word(t_token **token_lst, char *s, int index,
						int start);
int					save_sep(t_token **token_lst, char *s, int index, 
						int type);
int					set_quote_status(int quote_status, char c);
int					is_separator(char *s, int i);

// lexer/token_lst.c
t_token				*lst_new_token(char *value, int type, int quote_status);
void				lst_add_back_token(t_token **alst, t_token *node);
void				lstdelone_token(t_token *lst, void (*del)(void *));
void				lstclear_token(t_token **lst, void (*del)(void *));

//  --------------------------------------------------------------------------------
// |									PARSING										|
//  --------------------------------------------------------------------------------

// parsing/parser.c
bool				tokenize_and_parse(t_data *data);

// parsing/parse_word.c
void				parse_word(t_cmd **cmd, t_token **token_lst);
int					create_args(t_token **token_node, t_cmd *last_cmd);
int					count_args(t_token *temp);

// parsing/get_cmd.c
void				get_commands(t_data *data, t_token *token);

// parsing/cmd_lst.c
t_cmd				*lst_new_cmd(void);
void				lst_add_back_cmd(t_cmd **alst, t_cmd *node);
t_cmd				*lst_last_cmd(t_cmd *cmd);
void				lstdelone_cmd(t_cmd *lst, void (*del)(void *));
void				lstclear_cmd(t_cmd **lst, void (*del)(void *));

// parsing/debug.c
void				print_cmd(t_cmd *cmd);
void				print_token(t_token *token);

#endif
