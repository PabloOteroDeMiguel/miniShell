/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:41:53 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/08 18:11:37 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_pipex.h"

void	ft_infile(int fd, int fd1[2])
{
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(fd1[1], STDOUT_FILENO);
	close(fd1[1]);
}


void	ft_first_part(t_comm_path *act, char **envp, char **argv)
{
	// int			fd1[2];
	int			fd;
	int			fd2;
	int			status;
	int			pid;

	pid = fork();
	if (pid == -1)
		perror("Error");
	else if (pid == 0)
	{
		// close(fd1[0]);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			exit (0);
		dup2(fd, STDIN_FILENO);
		close(fd);
		// dup2(fd1[1], STDOUT_FILENO);
		// close(fd1[1]);
		if (execve(act->comm[0], act->comm, envp) < 0)
			exit (127);
		close(fd);
	}
	else
	{
		
		// close(fd1[1]);
		fd2 = open(argv[3], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd2 < 0)
			exit (0);
		
		// dup2(fd1[0], STDIN_FILENO);
		// close(fd1[0]);
		
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
	}
	// close(fd1[0]);
	
	write(2, "hola\n", 5);
	wait(&status);
	
}

