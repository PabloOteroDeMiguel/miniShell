# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: potero-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 12:55:48 by potero-d          #+#    #+#              #
#    Updated: 2022/04/04 12:45:06 by potero-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c min_argv.c min_lst.c min_builtins.c\
	   min_free.c min_env.c min_cd.c min_export.c

LIBFT_PATH = libft/

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

%.o:%.c
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(LIBFT_PATH) -I$(PIPEX_PATH) -I$(INCS) -I/Users/$(USER)/.brew/opt/readline/include
RM = rm -f

$(NAME): $(OBJS)
		@make -C $(LIBFT_PATH) --silent
		gcc -o $(NAME) $(OBJS) -I./libft -L./libft -lft  -I/Users/$(USER)/.brew/opt/readline/include -lreadline

all: $(NAME)  


sanitize: $(OBJS)
		@make -C $(LIBFT_PATH)  --silent
		gcc -o $(NAME) $(OBJS) -I./libft -L./libft -lft -I./pipex -L./pipex
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I./libft -L./libft -lft -fsanitize=address -g3 -O3

clean:
			$(RM) $(OBJS)
			@make -C $(LIBFT_PATH) clean --silent

fclean: clean
			$(RM) $(NAME)
			@make -C $(LIBFT_PATH) fclean --silent

re: fclean $(NAME)

.PHONY: all clean fcelan re
