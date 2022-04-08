/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:48:00 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/03/23 17:00:52 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_pipex.h"

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
