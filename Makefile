# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilymegy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 16:30:30 by ilymegy           #+#    #+#              #
#    Updated: 2023/12/13 16:30:31 by ilymegy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g3

INC				=	-I ./inc/\
					-I ./libft/

BUILTINS		=	builtins/cd.c \
					builtins/echo.c \
					builtins/env.c \
					builtins/exit.c \
					builtins/export.c \
					builtins/pwd.c \
					builtins/unset.c

CLEANING		=	clean/clean_it.c

EXEC			=	exec/exec.c

PARSING			=	parsing/parser.c

SRCS			=	$(BUILTINS)\
					$(CLEANING)\
					$(EXEC)\
					$(PARSING)\
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
				@$(CC) $(CFLAGS) -c $< -o $@ $(INC) -I$(READLINE_PATH)/include

$(OBJS): 		$(OBJ_PATH)

$(OBJ_PATH): 
				@mkdir $(OBJ_PATH)
				@mkdir $(OBJ_PATH)/clean
				@mkdir $(OBJ_PATH)/builtins
				@mkdir $(OBJ_PATH)/exec
				@mkdir $(OBJ_PATH)/parsing

$(LIBFT):
				@make -sC $(LIBFT_PATH) --no-print-directory
				@echo "Libft \033[1;32mOK\033[m"

$(NAME):		$(OBJS)
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
