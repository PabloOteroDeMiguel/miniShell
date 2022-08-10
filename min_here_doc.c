/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:14:21 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/10 13:58:19 by pmoreno-         ###   ########.fr       */
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

void	min_here_doc(t_argv *argv)
{
	int		fd[2];
	int		pid;
	int		status;

	pipe(fd);
	pid = fork();
	g_sign = pid;
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(fd[1]);
		close(fd[0]);
		run_here_doc(argv);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	signal(SIGINT, sighandlerhd);
	signal(SIGQUIT, SIG_IGN);
	g_sign = 3;
	wait(&status);
}
