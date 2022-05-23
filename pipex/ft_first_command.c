/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:41:53 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/05/23 15:11:37 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_infile(int fd, int fd1[2])
{
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(fd1[1], STDOUT_FILENO);
	close(fd1[1]);
}

void	ft_first_child(char **argv, int fd1[2], t_comm_path *act, char **envp)
{
	int	fd;

	close(fd1[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit (0);
	ft_infile(fd, fd1);
	if (execve(act->comm[0], act->comm, envp) < 0)
		exit (127);
}

void	ft_mid_part(t_comm_path *act, char **envp)
{
	int		fd[2];
	int		pid;

	pid = fork();
	if (pid == -1)
		perror("Error");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(act->comm[0], act->comm, envp) < 0)
			exit (127);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	ft_last_part(t_comm_path *act, char **argv, char **envp)
{
	int		fd;
	int		pid;

	pid = fork();
	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		exit (0);
	if (pid == -1)
		perror("Error");
	else if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if (execve(act->comm[0], act->comm, envp) < 0)
			exit (127);
	}
}

void	ft_first_part(t_comm_path *act, char **envp, char **argv, int tamlist)
{
	int			fd1[2];
	int			status;
	int			pid;
	int			list;

	list = tamlist;
	pipe(fd1);
	pid = fork();
	if (pid == -1)
		perror("Error");
	else if (pid == 0)
		ft_first_child(argv, fd1, act, envp);
	dup2(fd1[0], STDIN_FILENO);
	close(fd1[0]);
	close(fd1[1]);
	while (tamlist > 1)
	{
		act = act->next;
		ft_mid_part(act, envp);
		tamlist--;
	}
	ft_last_part(act->next, argv, envp);
	close(STDIN_FILENO);
	while (list > 0)
	{
		wait(&status);
		list--;
	}
}


