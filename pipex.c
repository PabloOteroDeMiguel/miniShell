/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:57:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/17 16:04:32 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mid_cmd(t_argv *arg, t_data *data)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			return (127);
	}
//	if (ft_strcmp(data->infile, "/dev/fd/0") != 0)
//	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	pipe_execute(t_data *data)
{
	int		fd;
	int		fd1[2];
	int		fd3;
	int		status;
	int		pid;
	t_argv	*arg;

	arg = *data->argv;
/*
	fd = open(data->infile, O_RDONLY);
	if (fd < 0)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
*/

	pipe(fd1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd1[0]);
	
		fd = open(data->infile, O_RDONLY);
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[1]);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			exit(127);
	}

//	write (2, "1\n", 2);
	if (data->num_argc > 1) //si solo hay un comando no hace nada
		arg = arg->next;
	close(fd1[1]);
	if (ft_strcmp(data->infile, "/dev/fd/0") != 0)
		dup2(fd1[0], STDIN_FILENO);
//	write (2, "2\n", 2);
	while (arg->next)
	{
		if (mid_cmd(arg, data) != 0)
			return (1);
		arg = arg->next;
	}
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		fd3 = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd3 < 0)
			return (1);
		dup2(fd3, STDOUT_FILENO);
		close(fd3);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			return (127);
	}
	close(STDIN_FILENO);
	arg = *data->argv;
	while (arg)
	{
		wait(&status);
		arg = arg->next;
	}
	return (0);
}
