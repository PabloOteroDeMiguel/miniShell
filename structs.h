/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:30:19 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/09 19:05:18 by potero           ###   ########.fr       */
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
	struct s_argv	*next;
}	t_argv;

typedef struct s_myenv
{
	char			*key;
	char			*value;
	struct s_myenv	*next;
}	t_myenv;

typedef struct s_data
{
	struct s_myenv	**myenv;
	struct s_argv	**argv;
	char			*infile;
	char			*outfile;
	char			**myenv_str;
	int				num_argc;
}	t_data;

#endif
