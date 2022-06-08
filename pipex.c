/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:57:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/08 16:36:40 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mid_cmd(t_argv *arg, t_data *data)
{
	int 	fd[2];
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
	//	ft_putstr_fd(direction[i - 2], 2);
	//	ft_putstr_fd(arg[0], 2);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			return (128);
	}
//	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (0);
}


int	pipe_execute(t_data *data)
{
//	int		fd;
	int		fd[2];
	int		fd3;
	int		status;
	int		pid;
	t_argv	*arg;
 	

	arg = *data->argv;
	pipe(fd);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		//close(fd[0]);
		fd[0] = open(data->infile, O_RDONLY);
		if (fd[0] < 0)
			return (0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			return (127);
	}
	if (data->num_argc > 1) //si solo hay un comando no hace nada
		arg = arg->next;
	//dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	while (arg->next)
	{
		if (mid_cmd(arg, data) != 0)
			return (1);
		arg = arg->next;
	}
	fd3 = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd3 < 0)
		return (0);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		dup2(fd3, STDOUT_FILENO);
		close(fd3);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			return (127);
	}
//	close(STDIN_FILENO);
	arg = *data->argv;
	while (arg)
	{
		wait(&status);
		arg = arg->next;
	}
	return (100);
}

/*
int	pipe_execute(t_data *data)
{
	int		fd;
	int		fd1[2];
	int		fd3;
	int		status;
	int		pid;
	t_argv	*arg;
 	

	arg = *data->argv;
//	ft_putstr_fd(arg[0], 1);
//	ft_putstr_fd(direction[i], 1);
	pipe(fd1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd1[0]);
		fd = open(data->infile, O_RDONLY);
		if (fd < 0)
			return (0);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[1]);
	//	ft_putstr_fd(direction[i - 2], 2);
	//	if (execve(data->dir_pipe[i], arg, data->myenv_str) < 0)
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			return (127);
	}
	if (data->num_argc > 1) //si solo hay un comando no hace nada
		arg = arg->next;
	dup2(fd1[0], STDIN_FILENO);
	close(fd1[0]);
	close(fd1[1]);
	while (arg->next)
	{
		if (mid_cmd(arg, data) != 0)
			return (1);
		arg = arg->next;
	}
	fd3 = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
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
	return (100);
}
*/
