/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:19:01 by potero-d          #+#    #+#             */
/*   Updated: 2022/01/18 13:31:24 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int *fd1, char **argv, char **envp, char *path)
{
	int		fd;
	char	**arg1;

	arg1 = ft_split(argv[2], ' ');
	close(fd1[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_fd_error(argv[1]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(fd1[1], STDOUT_FILENO);
	close(fd1[1]);
	if (execve(path, arg1, envp) < 0)
		exit(127);
}

void	second_child(int fd1, char **argv, char **envp, char *path)
{
	int		fd;
	char	**arg2;

	arg2 = ft_split(argv[3], ' ');
	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		ft_fd_error(argv[4]);
	dup2(fd1, STDIN_FILENO);
	close(fd1);
	dup2(fd, STDOUT_FILENO);
	if (execve(path, arg2, envp) < 0)
		exit(127);
}

int	ft_pipex(char **argv, char **envp, char **path)
{
	int	fd1[2];
	int	status;
	int	pid;

	pipe(fd1);
	pid = fork();
	if (pid == -1)
		perror("Error");
	else if (pid == 0)
		first_child(fd1, argv, envp, path[0]);
	else
	{
		close(fd1[1]);
		pid = fork();
		if (pid == -1)
			perror("Error");
		else if (pid == 0)
			second_child(fd1[0], argv, envp, path[1]);
		else
			close(fd1[1]);
	}
	wait(&status);
	wait(&status);
	return (0);
}
