/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:48:35 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/03/23 17:00:29 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PIPEX_H
# define MINI_PIPEX_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <errno.h>

//Commands list
typedef struct s_comm_path
{
	char				**comm;
	int					ok;
	struct s_comm_path	*next;
}	t_comm_path;

// List methods
void			ft_lstadd_back(t_comm_path **lst, t_comm_path *new);
t_comm_path		*ft_lstlast(t_comm_path *lst);
int				ft_lstsize(t_comm_path *lst);
t_comm_path		*ft_lstnew(char **content);

//ft_files.c
void			ft_open_infile(char *arc);
void			ft_open_outfile(char *arc);

//ft_error_func.c
void			ft_file_error(char *str);
void			ft_comm_error(char *str);
void			ft_check_errors(t_comm_path **comm_dir);
void			ft_command_validation(t_comm_path **comm_dir, char **argv,
					int ferror);
void			ft_error(t_comm_path **var, int e);

//ft_error_func2.c
void			ft_args_error(void);

// main.c
t_comm_path		**ft_accesslist(char **l_paths, char **argv, int argc);
char			*ft_envp_path(char **envp, int argc);
void			ft_add_path(char **l_paths, char *argv,
					t_comm_path **aux_l);
void			ft_valid_direction(t_comm_path	**comm_dir, char **argv);

// main_last_part.c
void			ft_final_part(t_comm_path **comm_dir, char **l_paths);

// ft_first_command.c
void			ft_first_child(char **argv, int fd1[2],
					t_comm_path *act, char **envp);
void			ft_second_part(t_comm_path *act, int *fd1,
					char **argv, char **envp);
void			ft_first_part(t_comm_path *act, char **envp, char **argv,
					int tamlist);
void			ft_infile(int fd, int fd1[2]);

//ft_free_variables.c
void			free_variables_list(char **list);
void			free_variables(t_comm_path **comm_dir);

int				ft_open_file(char **argv, int argc);

// Libft methods
void			ft_putstr_fd(char *s, int fd);
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
void			*ft_memcpy(void *dst, const void *src, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_comm_path		*ft_lstnew_error(char **content);
int				ft_lstsize(t_comm_path *lst);


int hijo(t_comm_path *act, char **argv, char **envp); 
void	ft_second_part2(t_comm_path *act, int fd1[2], char **envp);

#endif
