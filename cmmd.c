/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:20:12 by potero            #+#    #+#             */
/*   Updated: 2022/06/30 10:03:58 by potero-d         ###   ########.fr       */
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
		if (aux->direction == NULL)
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
	close(fd[1]);
}

int	execute(t_data *data)
{
	int			fd[2];
	int			status;
	pid_t		pid;
	t_argv		*arg;

	arg = *data->argv;
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		fd[0] = open(data->infile, O_RDONLY);
		if (fd[0] < 0)
			fd_error(data->infile);
		fd[1] = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd[1] < 0)
			fd_error(data->outfile);
		child(fd);
		if (execve(arg->direction, arg->split, data->myenv_str) < 0)
			exit(127);
	}
//	close(fd[0]);
	wait(&status);
	return (WEXITSTATUS(status));
}
