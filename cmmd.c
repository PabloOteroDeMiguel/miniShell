/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:20:12 by potero            #+#    #+#             */
/*   Updated: 2022/08/03 13:15:55 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	direction(t_data *data)
{
	char	**path;
	int		i;
	t_argv	*aux;

	aux = *data->argv;
	path = ft_split(cmmd_find_path(data->myenv_str), ':');
	i = 0;
	while (aux)
	{	
		aux->direction = cmmd_path(path, aux->split[0]);
		if (aux->direction == NULL && path != 0)
			aux->error_code = 127;
		else
			aux->error_code = 100;
		i++;
		aux = aux->next;
	}
	if (path != 0)
		free_env_char(path);
	else
		free(path);
}

static void	child(int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
}

static void	files(t_argv *arg)
{
	if (arg->infile == 0)
		arg->infile = ft_strdup("/dev/fd/0");
	if (arg->outfile == 0)
		arg->outfile = ft_strdup("/dev/fd/1");
}

static void	file_des(int fd[2], t_argv *arg)
{
	fd[0] = open(arg->infile, O_RDONLY);
	if (fd[0] < 0)
		fd_error(arg->infile);
	if (arg->out == 2)
		fd[1] = open(arg->outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd[1] = open(arg->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[1] < 0)
		fd_error(arg->outfile);
}

int	execute_cmmd(t_data *data)
{
	int			fd[2];
	int			status;
	pid_t		pid;
	t_argv		*arg;

	arg = *data->argv;
	pid = fork();
	g_sign = pid;
	files(arg);
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		file_des(fd, arg);
		child(fd);
		if (min_builtins(arg, data) == 0)
			exit (data->error_no);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			exit((int) errno);
	}
	wait(&status);
	return (WEXITSTATUS(status));
}
