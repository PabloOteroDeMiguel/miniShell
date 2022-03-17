/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:48:00 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/02/16 16:48:04 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open_infile(char *arc)
{
	int	fd;

	fd = open(arc, O_RDONLY);
	if (fd < 0)
		ft_file_error(arc);
	close(fd);
	exit (0);
}

void	ft_open_outfile(char *arc)
{
	int	fd;

	fd = open(arc, O_CREAT | O_WRONLY, 0666);
	close(fd);
}
