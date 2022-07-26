/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:53 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/26 16:37:34 by pmoreno-         ###   ########.fr       */
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
# include<errno.h>
# include<signal.h>
# include<termios.h>
# include "libft.h"
# include "structs.h"

extern  int sign;

void	rl_replace_line(const char *text, int clear_undo);
/*Main*/
int		execute(t_data *data);
int		main(int argc, char **argv2, char **envp);
int		cont_arg(t_argv **argv);

/*Argv*/
void	read_str(t_argv *argv, char *str);
int		words(char *str);
void	arguments(t_argv **argv, char *str);
void	min_split(t_data *data);

/*Free*/
void	free_arg_str(char *str, t_argv *argv);
void	free_env(t_myenv *myenv);
void	free_env_char(char **str);

/*List*/
t_argv	*lstnew(char *str);
int		lstsize(t_argv *argv);
t_argv	*lstlast(t_argv *lst);
void	lst_add_back(t_argv **argv, t_argv *new);
void	add_front(t_argv **argv, t_argv *new);

/*Echo*/
void	min_echo(t_argv **argv);
int		check_flags(char *flag);

/*PWD*/
void	min_pwd(t_myenv **myenv);

/*Env*/
t_myenv	*envnew(char *str);
t_myenv	*envlast(t_myenv *myenv);
void	env_add_back(t_myenv **myenv, t_myenv *new);
void	min_getenv(char **envp, t_myenv **myenv);
char	**env_to_char(t_myenv **myenv);

/*Cd*/
void	min_cd(t_data *data);
void	change_pwd(t_myenv **myenv);

/*Export*/
void	min_export(t_data *data);
t_myenv	*export_new(char *str);
int		exist_key(char *key, t_myenv *myenv);

/*Unset*/
void	min_unset(t_data *data);
void	aux_unset(t_myenv **myenv, t_argv *argv);

/*Expand*/
void	expand(t_data *data);
int		change(int i, char c);
char	*change_str(char *str, t_myenv **myenv, int *len);

/*Print*/
void	print_env(t_myenv **env);
void	print_list(t_argv **argv);

/*Cmmd*/
int		command(t_data *data);
int		execute_cmmd(t_data *data);
void	direction(t_data *data);

/*Cmmd_Path*/
int		cmmd_addarg(char **new_path, char *path, char *arg);
void	not_cmmd(char *str);
char	*cmmd_find_path(char **envp);
char	*cmmd_path(char **path, char *arg);

/*Pipex*/
int		pipe_execute(t_data *data);

/*Remove_quotes*/
char	*quotes(char *arg);
void	remove_quotes(t_argv **argv);

/*Error*/
int		command_found(t_data *data);
void	update_error(t_data *data);
void	pipe_error(t_data *data);
void	fd_error(char *str);

/*Files*/
void	check_files(t_data *data);
void	set_initial_files(t_data *data);
void	clean_split(t_argv *argv, int i, int z);

/*Infiles*/
void	set_infile(t_argv *argv, int i);
int		check_if_infile(t_argv *argv, int i);

/*Outfiles*/
void	set_outfile(t_argv *argv, int i);
int		check_if_outfile(t_argv *argv, int i);

/*SHLVL*/
char	*shlvl(char *str);

/*Builtins*/
int		min_builtins(t_argv *argv, t_data *data);
int		builtins_pipex(t_argv *argv, t_data *data);

/*Here_doc*/
void	min_here_doc(t_argv *arg);

#endif
