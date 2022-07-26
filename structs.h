/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:30:19 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/26 16:37:12 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef struct s_argv
{
	char			*arg;
	char			**split;
	char			*direction;
	int				error_code;
	int				quote;
	int				num_split;
	char			*infile;
	char			*outfile;
	int				out;
	int				fd_hd;
	char			*eof;
	struct s_argv	*next;
}	t_argv;

typedef struct s_myenv
{
	char			*key;
	char			*value;
	struct s_myenv	*next;
	int				shlvl;
}	t_myenv;

typedef struct s_data
{
	struct s_myenv	**myenv;
	struct s_argv	**argv;
	char			**myenv_str;
	int				num_argc;
	int				error_no;
}	t_data;

#endif
