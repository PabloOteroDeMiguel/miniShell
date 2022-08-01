/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:14:21 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/01 11:36:17 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_here_doc(t_argv *arg)
{
	int		fd;
	char	*str;

	fd = open(arg->infile, O_CREAT | O_RDWR | O_TRUNC, 0666);
	str = readline("> ");
	while (ft_strcmp(str, arg->eof) != 0 || !str)
	{
		g_sign = 2;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	g_sign = 0;
	free(str);
	close(fd);
}

void	min_here_doc(t_argv *argv)
{
	int		fd[2];
	int		pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[1]);
		close(fd[0]);
		run_here_doc(argv);
		exit(0);
	}
	signal(SIGINT, sighandler);
	close(fd[0]);
	close(fd[1]);
	wait(&status);
}
