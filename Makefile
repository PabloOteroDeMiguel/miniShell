# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 12:55:48 by potero-d          #+#    #+#              #
#    Updated: 2022/08/04 12:32:07 by potero-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NONE	= '\033[0m'
RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
YELLOW	= '\033[1;33m'
BLUE	= '\033[1;34m'

SRCS = main.c min_argv.c min_lst.c min_echo.c min_pwd.c min_exit.c\
	   min_free.c min_env.c min_cd.c min_export.c min_unset.c min_expand.c\
	   min_remove_quotes.c min_print.c min_error.c min_files.c min_shlvl.c\
	   cmmd.c cmmd_path.c pipex.c min_builtins.c min_here_doc.c\
	   min_infile.c min_outfile.c min_expand_two.c min_signal.c min_export_two.c\

LIBFT_PATH = libft/

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

%.o:%.c
		@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(LIBFT_PATH) -I$(INCS) -I/Users/$(USER)/.brew/opt/readline/include 

RM = rm -f

$(NAME): $(OBJS)
		@make -C $(LIBFT_PATH) --silent
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(INCS) -I./$(LIBFT_PATH) -L./$(LIBFT_PATH) -lft  -I/Users/$(USER)/.brew/opt/readline/include -L/Users/$(USER)/.brew/opt/readline/lib -lreadline # -fsanitize=address
		@echo $(GREEN)$(NAME)": ready to be executed"$(NONE)

all: $(NAME)  

clean:
			@$(RM) $(OBJS)
			@make -C $(LIBFT_PATH) clean --silent
			@echo $(RED)$(NAME)": objects removed"$(NONE)

fclean: clean
			@$(RM) $(NAME)
			@make -C $(LIBFT_PATH) fclean --silent
			@echo $(YELLOW)$(NAME)": files removed"$(NONE)

re: fclean $(NAME)

.PHONY: all clean fclean re
