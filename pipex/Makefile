SRCS	= 	main.c ft_lstadd_back.c ft_lstlast.c ft_split.c ft_strchr.c ft_strlcpy.c \
			ft_strlcat.c ft_strlen.c ft_strncmp.c ft_strjoin.c ft_memcpy.c ft_first_command.c \
			ft_putstr_fd.c ft_error_funct.c ft_files.c ft_free_variables.c ft_error_funct2.c \
			ft_lstnew.c main_last_part.c ft_open_file.c ft_prueba.c

OBJS	= $(SRCS:.c=.o)

NAME	= pipex

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
