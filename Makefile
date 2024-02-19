NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g3

INC				=	-I ./inc/ \
					-I ./libft/
INCS			=	./inc/*.h

BUILTINS		=	srcs/builtins/cd.c \
					srcs/builtins/echo.c \
					srcs/builtins/env.c \
					srcs/builtins/exit.c \
					srcs/builtins/export.c \
					srcs/builtins/export_utils.c \
					srcs/builtins/pwd.c \
					srcs/builtins/unset.c

CLEANING		=	srcs/clean/clean_it.c

EXEC			=	srcs/exec/exec.c \
					srcs/exec/exec_pipe.c \
					srcs/exec/init_structure.c \
					srcs/exec/init_env.c \
					srcs/exec/exec_utils.c \
					srcs/exec/exec_redir.c \
					srcs/exec/exec_get_path.c \
					srcs/exec/exec_errors.c \
					srcs/exec/exec_builtins.c

EXPAND			=	srcs/expand/expand.c \
					srcs/expand/expander_heredoc.c \
					srcs/expand/expand_utils.c \
					srcs/expand/expand_split.c \
					srcs/expand/expand_strip.c \
					srcs/expand/expand_clean.c

ERROR			=	srcs/err_handler/error_handler.c \
					srcs/err_handler/error_utils.c \
					srcs/err_handler/error_parsing.c

LEXER			=	srcs/lexer/token.c \
					srcs/lexer/token_utils.c \
					srcs/lexer/token_lst.c \
					srcs/lexer/syntax_error.c

PARSING			=	srcs/parsing/get_cmd.c \
					srcs/parsing/handle_word.c \
					srcs/parsing/handle_redir.c \
					srcs/parsing/cmd_lst.c \
					srcs/parsing/get_args.c \
					srcs/parsing/io_utils.c \
					srcs/parsing/debug.c

UTILS			=	srcs/utils/lst_manip.c \
					srcs/utils/singletons.c

SIGNALS			=	srcs/signals/signals_parent.c \
					srcs/signals/signals_exec.c

SRCS			=	$(BUILTINS)\
					$(CLEANING)\
					$(EXEC)\
					$(EXPAND)\
					$(LEXER)\
					$(PARSING)\
					$(UTILS)\
					$(ERROR)\
					$(SIGNALS)\
					srcs/main.c

LIBFT_PATH 		=	srcs/libft/
LIBFT_NAME		=	libft
LIBFT			=	$(LIBFT_PATH)$(LIBFT_NAME)

OBJ_PATH		=	obj/
OBJ				=	$(SRCS:.c=.o)
OBJS			=	$(addprefix $(OBJ_PATH), $(OBJ))
OBJSF			=	.cache_exists

READLINE_PATH	=	/goinfre/homebrew/opt/readline

all:			$(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
				@mkdir -p $(OBJ_PATH)
				@mkdir -p $(OBJ_PATH)/srcs
				@mkdir -p $(OBJ_PATH)/srcs/clean
				@mkdir -p $(OBJ_PATH)/srcs/expand
				@mkdir -p $(OBJ_PATH)/srcs/builtins
				@mkdir -p $(OBJ_PATH)/srcs/exec
				@mkdir -p $(OBJ_PATH)/srcs/lexer
				@mkdir -p $(OBJ_PATH)/srcs/parsing
				@mkdir -p $(OBJ_PATH)/srcs/utils
				@mkdir -p $(OBJ_PATH)/srcs/signals
				@mkdir -p $(OBJ_PATH)/srcs/err_handler
				@$(CC) $(CFLAGS) -c $< -o $@ $(INC) -I$(READLINE_PATH)/include

$(LIBFT):
				@make -sC $(LIBFT_PATH) --no-print-directory
				@echo "Libft \033[1;32mOK\033[m"

$(NAME):		$(OBJS) $(SRCS) $(INCS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC) -L$(READLINE_PATH)/lib -lreadline
				@echo "minishell \033[1;32mOK\033[m"

clean:
				@rm -rf $(OBJ_PATH)
				@rm -f $(OBJSF)
				@make clean -C $(LIBFT_PATH) --no-print-directory

fclean:			clean
				@rm -rf $(NAME)
				@make fclean -C $(LIBFT_PATH) --no-print-directory

re:				fclean all
