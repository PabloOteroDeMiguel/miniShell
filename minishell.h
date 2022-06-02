/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:53 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/02 19:48:04 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<fcntl.h>
//# include "pipex/inc/pipex.h"
# include "libft.h"
# include "structs.h"
//# include "execute.h"

/*Main*/
int		main(int argc, char **argv2, char **envp);
void	print_list(t_argv **argv);
int		min_builtins(char *str, t_data *data);

/*Argv*/
void	read_str(t_argv *argv, char *str);
int		words(char *str);
void	arguments(t_argv **argv, char *str);
void	min_split(t_argv **argv);

/*Free*/
void	free_arg_str(char *str, t_argv *argv);
void	free_env(t_myenv *myenv);
void	free_env_char(char **str);

/*List*/
t_argv	*lstnew(char *str, int q);
int		lstsize(t_argv *argv);
t_argv	*lstlast(t_argv *lst);
void	lst_add_back(t_argv **argv, t_argv *new);
void	add_front(t_argv **argv, t_argv *new);

/*Builtins*/
int     check_flags(char *flag);
void	min_echo(t_argv **argv);
void	min_pwd(t_myenv **myenv);

/*Env*/
t_myenv	*envnew(char *str);
t_myenv	*envlast(t_myenv *myenv);
void	env_add_back(t_myenv **myenv, t_myenv *new);
void	min_getenv(char **envp, t_myenv **myenv);
void	print_env(t_myenv **env);
char	**env_to_char(t_myenv **myenv);

/*Cd*/
void	min_cd(t_data *data);
void	change_pwd(t_myenv **myenv);

/*Export*/
void	min_export(t_data *data);
t_myenv	*export_new(char *str);
int		exist_key(char *key, t_myenv *myenv);

/*Unset*/
void	min_unset(t_myenv **myenv, t_argv *argv);

/*Expand*/
void	expand(t_data *data);
char	*change_str(char *str, t_myenv **myenv);

/*Cmmd*/
//int		command(char **argv, char **envp);
int		command(t_data *data);
//int		execute(char **argv, char **envp, char *direction);
int		execute(t_data *data, char *direction);;

/*Cmmd_Path*/
int		cmmd_addarg(char    **new_path, char *path, char *arg);
void	not_cmmd(char *str);
char	*cmmd_find_path(char **envp);
char	*cmmd_path(char **path, char *arg);

#endif
