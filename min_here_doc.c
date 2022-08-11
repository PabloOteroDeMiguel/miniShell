/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:14:21 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/11 10:17:32 by pmoreno-         ###   ########.fr       */
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
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	if (str)
		free(str);
	close(fd);
}

static void	aux_here_doc(int fd[2], t_argv *argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[1]);
	close(fd[0]);
	run_here_doc(argv);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	exit(0);
}

void	min_here_doc(t_argv *argv)
{
	int		fd[2];
	int		pid;
	int		status;

	pipe(fd);
	pid = fork();
	g_sign[0] = pid;
	g_sign[1] = 1;
	if (pid == -1)
		return ;
	else if (pid == 0)
		aux_here_doc(fd, argv);
	close(fd[0]);
	close(fd[1]);
	wait(&status);
}
