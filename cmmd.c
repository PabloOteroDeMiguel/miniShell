/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:20:12 by potero            #+#    #+#             */
/*   Updated: 2022/06/08 16:35:26 by potero           ###   ########.fr       */
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
	//	printf("dir->%s\n", aux->direction);
	//	printf("dir->%p\n", aux->direction);
		if (aux->direction == NULL)
			aux->error_code = 127;
		else
		{
			aux->error_code = 100;
		}
		i++;
		aux = aux->next;
	}
	free_env_char(path);
}

/*
int	command(t_data *data)
{
	t_argv	*aux;

	aux = *data->argv;
	if (aux->error_code == 100)	
		aux->error_code = execute(data, aux->direction);
	return (aux->error_code);
}
*/
/*
int	execute(t_data *data, char *direction)
{
	int			fd[2];
	int			status;
	int			pid;
	t_argv		*arg;

	arg = *data->argv;
	pid = fork();
	fd[0] = open(data->infile, O_RDONLY);
	if (fd[0] < 0)
		return (0);
	fd[1] = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd[1] < 0)
		return (0);
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(direction, arg->split, data->myenv_str) < 0)
			return (127);
	}
	close(fd[0]);
	wait(&status);
	return (100);
}
*/
