/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:57:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/05/30 11:38:42 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_env_char(char **str)
{
	int i;
	
	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}	

int	execute(int argc, char **argv, char **envp, char **direction);

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	char	***arg;
	char	**direction;
	int 	i;
//	int j;

	direction = malloc(sizeof(char *) * argc - 2);
	arg = malloc(sizeof(char **) * argc - 2);
	*direction = 0;
	path = ft_split(ft_find_path(envp), ':');
	i = 0;
	while (i + 2 < argc - 1)
	{
//	j = 0;
		arg[i] = ft_split(argv[i + 2], ' ');
		direction[i] = ft_path(path, arg[i][0]);
/*	while (arg[i][j])
		{
			printf("arg[%i][%i]->%s\n", i , j, arg[i][j]);
			j++;
		}
		printf("dir[%i]->%s\n", i, direction[i]);
		i++;*/
	}
//	ft_valid_direction(direction, argv); I need think something about it
	execute(argc, argv, envp, direction);
}

int	mid_cmd(int i, char **direction, char **argv, char **envp)
{
	int 	fd[2];
	int		pid;
	char	**arg;

	arg = ft_split(argv[i], ' ');
	pipe(fd);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	//	ft_putstr_fd(direction[i - 2], 2);
	//	ft_putstr_fd(arg[0], 2);
		if (execve(direction[i - 2], arg, envp) < 0)
			return (128);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	free_env_char(arg);
	return (0);
}

int	execute(int argc, char **argv, char **envp, char **direction)
{
	int		fd;
	int		fd1[2];
	int		fd3;
	int		status;
	int		pid;
	char	**arg;
	int		i;
	
	
	i = 2;
	arg = ft_split(argv[i], ' ');
//	ft_putstr_fd(arg[0], 1);
//	ft_putstr_fd(direction[i], 1);
	pipe(fd1);
	pid = fork();
	if (pid == -1)
		return (1);
	//	perror("Error");
	else if (pid == 0)
	{
		close(fd1[0]);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (0);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[1]);
	//	ft_putstr_fd(direction[i - 2], 2);
		if (execve(direction[i - 2], arg, envp) < 0)
			return (127);
	}
	i++;
	dup2(fd1[0], STDIN_FILENO);
	close(fd1[0]);
	close(fd1[1]);
	free_env_char(arg);
	while (i < argc - 2)
	{
		if (mid_cmd(i, direction, argv, envp) != 0)
			return (1);
		i++;
	}

	arg = ft_split(argv[i], ' ');
	fd3 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd3 < 0)
		return (0);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		dup2(fd3, STDOUT_FILENO);
		close(fd3);
	//	ft_putstr_fd(direction[i -2], 2);
	//	ft_putstr_fd(arg[0], 2);
		if (execve(direction[i - 2], arg, envp) < 0)
			return (129);
	}
	free_env_char(arg);
	close(STDIN_FILENO);
	while (i >= 2)
	{
		wait(&status);
		i--;
	}
	return (100);
}
