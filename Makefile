# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilymegy <ilyanamegy@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 16:30:30 by ilymegy           #+#    #+#              #
#    Updated: 2023/12/27 20:43:25 by ilymegy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g3

INC				=	-I ./inc/\
					-I ./libft/
INCS			= ./inc/*.h

BUILTINS		=	builtins/cd.c \
					builtins/echo.c \
					builtins/env.c \
					builtins/exit.c \
					builtins/export.c \
					builtins/export_utils.c \
					builtins/pwd.c \
					builtins/unset.c

CLEANING		=	clean/clean_it.c

EXEC			=	exec/exec.c \
					exec/exec_builtin.c

ERROR			=	err_handler/error_handler.c

PARSING			=	parsing/parser.c

SRCS			=	$(BUILTINS)\
					$(CLEANING)\
					$(EXEC)\
					$(PARSING)\
					$(ERROR)\
					main.c

LIBFT_PATH 		=	libft/
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
				@mkdir -p $(OBJ_PATH)/clean
				@mkdir -p $(OBJ_PATH)/builtins
				@mkdir -p $(OBJ_PATH)/exec
				@mkdir -p $(OBJ_PATH)/parsing
				@mkdir -p $(OBJ_PATH)/err_handler
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
