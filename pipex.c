/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:57:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/19 13:49:59 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_pipex(t_argv *argv, t_data *data)
{
	int r;

	r = 0;
	if ((ft_strcmp(argv->split[0], "echo") == 0)
		|| (ft_strncmp(argv->split[0], "ECHO", 4) == 0))
			min_echo(data->argv);
	else if (ft_strcmp(argv->split[0], "pwd") == 0
		|| ft_strcmp(argv->split[0], "PWD") == 0)
			min_pwd(data->myenv);
	else if (ft_strcmp(argv->arg, "env") == 0
		|| ft_strcmp(argv->arg, "ENV") == 0)
			print_env(data->myenv);
	else
		r = 1;
	return (r);
}

int	first_cmmd(t_argv *arg, t_data *data, int fd1[2])
{
	int	fd;
	pid_t	pid;
	int	status;

	pipe(fd1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(fd1[0]);
		fd = open(arg->infile, O_RDONLY);
		if (fd < 0)
			fd_error(arg->infile);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[1]);
	//	builtins_pipex(arg, data);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
				exit(127);
	}
	wait(&status);
	return (0);
}

int	mid_cmd(t_argv *arg, t_data *data)
{
	int		fd[2];
	pid_t	pid;
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
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		fd = open(arg->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd < 0)
			fd_error(arg->outfile);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			return (127);
	}
	return (0);
}
/*
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
*/

int	pipe_execute(t_data *data)
{
	int		fd[2];
	int		fd_last;
	int		status;
	pid_t	pid;
	t_argv	*arg;

	arg = *data->argv;
	while (arg->next)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			return (1);
		else if (pid == 0)
		{
		//	dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			if (arg->infile != 0)
			{
				fd[0] = open(arg->infile, O_RDONLY);
				if (fd[0] < 0)
					fd_error(arg->infile);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
			}

			if (arg->outfile != 0)
			{
				fd[1] = open(arg->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
				if (fd[1] < 0)
					fd_error(arg->outfile);
			}

		//	dup2(fd[0], STDIN_FILENO);
		//	close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			if (execve(arg->direction, arg->split, data->myenv_str) < 0)
				exit(127);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	//	close(STDIN_FILENO);
		wait(&status);
		arg = arg->next;
	}
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		fd_last = open(arg->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		/*
		if (arg->outfile != 0)
		{
			fd_last = open(arg->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (fd_last < 0)
				fd_error(arg->outfile);
		}
		*/
		dup2(fd_last, STDOUT_FILENO);
		close(fd_last);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			exit(127);
	}
	close(STDIN_FILENO);
	wait(&status);
	return (WEXITSTATUS(status));
}
