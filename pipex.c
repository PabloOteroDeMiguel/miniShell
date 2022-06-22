/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:57:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/22 11:45:22 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_cmmd(t_argv *arg, t_data *data, int fd1[2])
{
	int	fd;
	int	pid;
	int	status;

	pipe(fd1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd1[0]);
		fd = open(data->infile, O_RDONLY);
		if (fd < 0)
			fd_error(data->infile);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[1]);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			exit(127);
	}
	wait(&status);
	return (0);
}

int	mid_cmd(t_argv *arg, t_data *data)
{
	int		fd[2];
	int		pid;
	int		status;

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
			exit(127);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	wait(&status);
	return (0);
}

int	last_cmmd(t_argv *arg, t_data *data)
{
	int	fd;
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		fd = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd < 0)
			fd_error(data->outfile);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			return (127);
	}
	return (0);
}

int	pipe_execute(t_data *data)
{
	int		fd1[2];
	int		status;
	t_argv	*arg;

	arg = *data->argv;
	if (first_cmmd(arg, data, fd1) != 0)
		return (1);
	arg = arg->next;
	close(fd1[1]);
	dup2(fd1[0], STDIN_FILENO);
	while (arg->next)
	{
		if (mid_cmd(arg, data) != 0)
			return (1);
		arg = arg->next;
	}
	if (last_cmmd(arg, data) != 0)
		return (1);
	close(STDIN_FILENO);
	wait(&status);
	return (WEXITSTATUS(status));
}
