/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:57:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/07 16:26:11 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mid_cmd(int i, t_data *data)
{
	int 	fd[2];
	int		pid;
	char	**arg;

	arg = ft_split(data->arg_pipe[i], ' ');
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
		if (execve(data->dir_pipe[i], arg, data->myenv_str) < 0)
			return (128);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	free_env_char(arg);
	return (0);
}

int	pipe_execute(t_data *data)
{
	int		fd;
	int		fd1[2];
	int		fd3;
	int		status;
	int		pid;
	char	**arg;
	int		i;
	
/*Hacer que la funcion commmand (cmmd.c) meta las direcciones dentro de la 
 * estructura argv (hacer un while)
 * diseñar algo con if dependiedno que comando es si abrir un fd u otro
*/
 	
	i = 0;
	arg = ft_split(data->arg_pipe[i], ' ');
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
		fd = open(data->infile, O_RDONLY);
		if (fd < 0)
			return (0);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[1]);
	//	ft_putstr_fd(direction[i - 2], 2);
		if (execve(data->dir_pipe[i], arg, data->myenv_str) < 0)
			return (127);
	}
	i++;
	dup2(fd1[0], STDIN_FILENO);
	close(fd1[0]);
	close(fd1[1]);
	free_env_char(arg);
	while (i < data->num_argc)
	{
		if (mid_cmd(i, data) != 0)
			return (1);
		i++;
	}

	arg = ft_split(data->arg_pipe[i], ' ');
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
		if (execve(data->dir_pipe[i], arg, data->myenv_str) < 0)
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
