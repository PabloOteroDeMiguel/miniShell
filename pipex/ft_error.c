/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:36:18 by potero-d          #+#    #+#             */
/*   Updated: 2022/01/18 11:53:11 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_not_cmd(char *str)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
}

void	ft_fd_error(char *str)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, ": ", 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	exit (1);
}

void	ft_valid_direction(char	**direction, char **argv)
{
	if (direction[0] == NULL)
	{
		if (direction[1] == NULL)
			exit (127);
		else
			direction[0] = argv[2];
	}
	else
		if (direction[1] == NULL)
			direction[1] = argv[3];
}

void	ft_argc(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 2);
		exit (1);
	}
}
