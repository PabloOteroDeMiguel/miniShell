/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:53 by potero-d          #+#    #+#             */
/*   Updated: 2022/04/04 12:29:11 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<readline/readline.h>
# include<readline/history.h>
//# include "pipex/inc/pipex.h"
# include "libft.h"
# include "structs.h"

/*Main*/
//int		main(void);
//int		main(int argc, char **argv2, char **envp);
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

/*List*/
t_argv	*lstnew(char *str, int q);
int		lstsize(t_argv *argv);
t_argv	*lstlast(t_argv *lst);
void	lst_add_back(t_argv **argv, t_argv *new);
void	add_front(t_argv **argv, t_argv *new);

/*Builtins*/
void	min_echo(t_argv **argv);
void	min_pwd(t_myenv **myenv);

/*Env*/
t_myenv	*envnew(char *str);
t_myenv	*envlast(t_myenv *myenv);
void	env_add_back(t_myenv **myenv, t_myenv *new);
void	min_getenv(char **envp, t_myenv **myenv);
void	print_env(t_myenv **env);

/*Cd*/
void	min_cd(t_data *data);
void	change_pwd(t_myenv **myenv);

#endif
