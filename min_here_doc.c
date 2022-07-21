/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:14:21 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/21 13:01:32 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_here_doc(t_argv *arg)
{
	int		fd;
	char	*str;

	fd = open(arg->infile, O_CREAT | O_RDWR | O_TRUNC,  0666);
	str = readline("> ");
	while (ft_strcmp(str, arg->eof) != 0)
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	close(fd);
}
