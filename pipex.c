/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:57:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/27 12:14:07 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_execute(t_data *data)
{
	int		fd[2];
	int		status;
	pid_t	pid;
	t_argv	*arg;

	arg = *data->argv;
	while (arg)
	{
		if (arg->next)
			pipe(fd);
		pid = fork();
		if (pid == -1)
			return (1);
		else if (pid == 0)
		{
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
				if (arg->out == 2)
					fd[1] = open(arg->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
				else
					fd[1] = open(arg->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (fd[1] < 0)
					fd_error(arg->outfile);
			}
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			if (min_builtins(arg, data) == 0)
			{
				write(1, "It's builtin\n", 13);
				exit(0);
			}
			if (execve(arg->direction, arg->split, data->myenv_str) < 0)
				exit(127);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		wait(&status);
		arg = arg->next;
	}
	close(STDIN_FILENO);
	return (WEXITSTATUS(status));
}
