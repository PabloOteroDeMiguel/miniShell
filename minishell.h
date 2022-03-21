/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:53 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/21 12:16:43 by potero-d         ###   ########.fr       */
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
//int	main(int argc, char *argv[]);
int	main(void);

/*Argv*/
void	read_str(t_argv *argv, char *str);
int		words(char *str);
void	arguments(t_argv *argv, char *str);

/*Free*/
void	free_arg_str(char *str, t_argv *argv);

#endif
