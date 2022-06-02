/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:20:12 by potero            #+#    #+#             */
/*   Updated: 2022/05/11 12:14:42 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command(char **argv, char **envp)
{
	char	**path;
	char	**arg;
	char	*direction;
	int		r;

	arg = ft_split(argv[1], ' ');
	path = ft_split(cmmd_find_path(envp), ':');
	direction = cmmd_path(path, arg[0]);
	if (direction == NULL)
		return (127);
	r = execute(argv, envp, direction);
	
	free_env_char(arg);
	free_env_char(path);
	free(direction);
	return (r);
}

int	execute(char **argv, char **envp, char *direction)
{
	int			fd;
	int			fd2;
	int			status;
	int			pid;
	char 		**arg;

	arg = ft_split(argv[1], ' ');
	pid = fork();
	fd = open(argv[0], O_RDONLY);
	if (fd < 0)
		return (0);
	fd2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd2 < 0)
		return (0);
	if (pid == -1)
		return (1);
	//	perror("Error");
	else if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		if (execve(direction, arg, envp) < 0)
			return (127);
			//exit (127);
	}
	close(fd);
	wait(&status);
	free_env_char(arg);
	return (100);
}
