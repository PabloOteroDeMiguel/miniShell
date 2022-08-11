/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:57:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/11 11:59:13 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_files(t_argv *arg, int fd[2])
{
	if (arg->infile != 0)
	{
		fd[0] = open(arg->infile, O_RDONLY);
		if (fd[0] < 0)
			fd_error(arg->infile);
	//	dup2(fd[0], STDIN_FILENO);
	//	close(fd[0]);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (arg->outfile != 0)
	{
		if (arg->out == 2)
			fd[1] = open(arg->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd[1] = open(arg->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd[1] < 0)
			fd_error(arg->outfile);
	}
}

static void	child(int fd[2], t_argv *arg, t_data *data)
{
	if (g_sign[1] == 2)
		exit (0);
	close(fd[0]);
	open_files(arg, fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (arg->error_code == 127)
		exit (127);
	if (min_builtins(arg, data) == 0)
		exit(data->error_no);
	if (execve(arg->direction, arg->split, data->myenv_str) < 0)
		exit(child_error(arg, (int) errno));
	close(fd[0]);
	close(fd[1]);
}

static int	wait_status(t_data *data)
{
	t_argv	*arg;
	int		status;

	arg = *data->argv;
	while (arg)
	{
		wait(&status);
		arg = arg->next;
	}
	return (status);
}

int	pipe_execute(t_data *data)
{
	int		fd[2];
	pid_t	pid;
	t_argv	*arg;
	int		status;

	arg = *data->argv;
	while (arg)
	{
		if (arg->next)
			pipe(fd);
		pid = fork();
		g_sign[0] = pid;
		if (pid == -1)
			return (1);
		else if (pid == 0)
			child(fd, arg, data);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(STDIN_FILENO);
		arg = arg->next;
	}
//	close(fd[0]);
//	close(fd[1]);
	status = wait_status(data);
	close(STDIN_FILENO);
	return (WEXITSTATUS(status));
}
