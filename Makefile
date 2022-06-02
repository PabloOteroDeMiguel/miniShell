# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 12:55:48 by potero-d          #+#    #+#              #
#    Updated: 2022/06/01 20:25:37 by pmoreno-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c min_argv.c min_lst.c min_builtins.c\
	   min_free.c min_env.c min_cd.c min_export.c min_unset.c min_expand.c\
	   cmmd.c cmmd_path.c
##	   execute/ft_lstadd_back.c execute/ft_lstlast.c execute/ft_error_funct.c\
	   execute/ft_files.c execute/ft_free_variables.c execute/ft_error_funct2.c\
	   execute/ft_lstnew.c execute/main_last_part.c execute/ft_open_file.c\
	   execute/ft_first_command.c execute/execute.c

LIBFT_PATH = libft/

OBJS = $(SRCS:.c=.o)

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -O0

%.o:%.c
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(LIBFT_PATH) -I$(EXECT_PATH) -I$(INCS) -I/Users/$(USER)/.brew/opt/readline/include
RM = rm -f

$(NAME): $(OBJS)
		@make -C $(LIBFT_PATH) --silent
		gcc -o $(NAME) $(OBJS) -I./libft -L./libft -lft -I/Users/$(USER)/.brew/opt/readline/include -lreadline -fsanitize=address

all: $(NAME)  


sanitize: $(OBJS)
		@make -C $(LIBFT_PATH)  --silent
		gcc -o $(NAME) $(OBJS) -I./libft -L./libft -lft
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I./libft -L./libft -lft -fsanitize=address -g3 -O3

clean:
			$(RM) $(OBJS)
			@make -C $(LIBFT_PATH) clean --silent

fclean: clean
			$(RM) $(NAME)
			@make -C $(LIBFT_PATH) fclean --silent

re: fclean $(NAME)

.PHONY: all clean fcelan re
