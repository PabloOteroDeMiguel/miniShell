SRCS	= 	main.c ft_lstadd_back.c ft_lstlast.c ft_error_funct.c ft_files.c \
			ft_free_variables.c ft_error_funct2.c \
			ft_lstnew.c main_last_part.c ft_open_file.c ft_first_command.c

OBJS	= $(SRCS:.c=.o)

NAME	= mini_pipex

CFLAGS	= -Wall -Werror -Wextra 

GCC	= gcc

RM	= rm -f

all:		$(NAME)

.c.o:
	$(GCC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:		
	$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re 
