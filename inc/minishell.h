/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltorkia <ltorkia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:35:11 by ilymegy           #+#    #+#             */
/*   Updated: 2024/01/20 00:03:39 by ltorkia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <termios.h>

# define PROMPT "minishell$ "
# define HEREDOC_NAME "/tmp/.heredoc_"

# define ADD 1
# define RM 2
# define GET 3

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
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

//  --------------------------------------------------------------------------------
// |								PARSING											|
//  --------------------------------------------------------------------------------

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}					t_io_type;

typedef struct s_io_cmd
{
	t_io_type		type;
	char			*path;
	char			**expanded_value;
	int				here_doc;
	struct s_io_cmd	*next;
	struct s_io_cmd	*prev;
}					t_io_cmd;

/**
 * @brief  return char *cmd, char *path, char **args, int fd_in, int fd_out,
	bool pipe_out, t_cmd *prev, t_cmd *next
 * @note   return var cmd, var path, var args, var fd_in, var fd_out,
	var pipe_out, prev var, next var
*/
typedef struct s_cmd
{
	t_io_cmd		*io_list;
	char			*cmd;
	char			**args;
	char			**expanded_args;
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
	int				stdin;
	int				stdout;
	bool			signint_child;
	bool			heredoc_sigint;
}					t_data;

//  --------------------------------------------------------------------------------
// |								ENUMS											|
//  --------------------------------------------------------------------------------

typedef enum e_token_type
{
	WHITESPACE = 1,
	WORD,
	VAR,     // $
	PIPE,    // |
	INPUT,   // <
	TRUNC,   // >
	HEREDOC, // <<
	APPEND   // >>
}					t_token_type;

typedef enum e_err_msg
{
	ERR_SYNTAX = -1,
	ERR_NOCMD = 0,
	ERR_ARGS,
	ERR_PATH,
	ERR_NOFILEDIR,
	ERR_EXPORT,
	ERR_UNSET,
	ERR_EXIT_NB,
	ERR_AMBIG_REDIR,
	ERR_PERM_DENIED
}					t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}					t_err_no;

typedef enum e_cmd_direction
{
	LEFT,
	RIGHT
}					t_cmd_direction;

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
void				ft_exit(t_data *data, t_cmd *cmd);

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
void				err_syntax(int err, char *s);
void				err_quote(char c);

//  --------------------------------------------------------------------------------
// |								EXECUTION										|
//  --------------------------------------------------------------------------------

typedef struct s_err
{
	t_err_no		no;
	t_err_msg		msg;
	char			*cause;
}					t_err;

typedef struct s_path
{
	t_err			err;
	char			*path;
}					t_path;

// exec/init_structure.c
void				init_cmdlst(t_data *data, t_cmd *cmd);

// exec/exec.c
int					exec_simple_cmd(t_data *data, t_cmd *cmd, bool piped);
void				executie(t_data *data, t_cmd *cmd, bool piped);

// exec/exec_builtin.c
int					is_builtin(char *arg);
int					exec_builtin(t_data *data, t_cmd *cmd);

// exec/exec_utils.c
int					close_n_wait(int fd[2], int p_first, int p_sec);
int					get_exit_status(int status);
int					check_redir(t_cmd *cmd);
void				get_out(t_data *data, int status, char **env);
void				reset_stds(t_data *data, bool piped);

// exec/exec_redir.c
int					check_write(char *file);
int					check_read(char *file);
int					open_in(t_io_cmd *io_lst, int *status);
int					open_out(t_io_cmd *io_lst, int *status);
int					open_append(t_io_cmd *io_lst, int *status);

// exec/exec_get_path.c
t_path				get_path(char *cmd);
t_err				check_exec(char *file, bool cmd);
// static char			*get_env_path(char *cmd, char *path);

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
int					save_word(t_token **token_lst, char *s, int index);
int					save_sep(t_token **token_lst, char *s, int index,
						t_token_type sep_type);

// lexer/token_utils.c
int					ignore_spaces(char *s, int index);
int					is_separator(char *s, int i);
bool				is_quote(char *s, int index);
bool				ignore_quotes(char *s, int *index);

// lexer/token_lst.c
t_token				*lst_new_token(char *value, t_token_type type);
void				lst_add_front_token(t_token **alst, t_token *node);
void				lst_add_back_token(t_token **alst, t_token *node);
void				lstdelone_token(t_token *lst, void (*del)(void *));
void				lstclear_token(t_token **lst, void (*del)(void *));

// lexer/syntax_error.c
bool				check_syntax(t_token *token);

//  --------------------------------------------------------------------------------
// |									PARSING										|
//  --------------------------------------------------------------------------------

// parsing/get_cmd.c
bool				get_commands(t_data *data, t_token *token);

// parsing/handle_word.c
bool				handle_word(t_cmd **cmd, t_token **token_lst);

// parsing/handle_sep.c
bool	handle_redir(t_cmd **last_cmd,
					t_token **token_lst,
					t_token_type type);

// parsing/get_args.c
bool				create_args(t_token **token_node, t_cmd *last_cmd);
bool				args_default(t_token **token_node, t_cmd **last_cmd,
						int *index);
int					count_args(t_token *temp);
bool				set_cmd_without_args(t_data *data);

// parsing/cmd_lst.c
t_cmd				*lst_new_cmd(void);
void				lst_add_back_cmd(t_cmd **alst, t_cmd *node);
t_cmd				*lst_last_cmd(t_cmd *cmd);
void				lstdelone_cmd(t_cmd *lst, void (*del)(void *));
void				lstclear_cmd(t_cmd **lst, void (*del)(void *));

//parsing/io_utils.c
bool				init_io_cmd(t_cmd **cmd);
void				lstdelone_io_list(t_io_cmd *io_list, void (*del)(void *));
void				lstclear_io_list(t_io_cmd **io_list, void (*del)(void *));

// parsing/debug.c
void				print_cmd(t_cmd *cmd);
void				print_token(t_token *token);

//  --------------------------------------------------------------------------------
// |									EXPAND										|
//  --------------------------------------------------------------------------------

//	expand/expand.c
char				**expander(char *str);

//	expand/expand_utils.c
char				*handle_single_quotes(char *s, int *i);
char				*handle_double_quotes(char *s, int *i);
char				*handle_dollar(char *s, int *i);
char				*handle_normal_str(char *s, int *i);

// expand/expand_clean.c
char				*ft_clean_empty_strs(char *str);

// expand/expand_split.c
char				**expand_split(char *s);

// expand/expander_heredoc.c
void				heredoc_expander(char *str, int fd);

//expand/remove_quotes.c
void				remove_quotes(t_cmd	**cmd);

#endif
