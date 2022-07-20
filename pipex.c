/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:57:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/20 13:05:14 by potero-d         ###   ########.fr       */
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
				fd[1] = open(arg->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
				if (fd[1] < 0)
					fd_error(arg->outfile);
			}
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);

			if (builtins_pipex(arg, data) == 0)
				printf("builtin\n");
			else
			{
				if (execve(arg->direction, arg->split, data->myenv_str) < 0)
					exit(127);
			}
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
