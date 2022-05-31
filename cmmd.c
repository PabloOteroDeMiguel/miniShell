/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:20:12 by potero            #+#    #+#             */
/*   Updated: 2022/05/31 14:49:18 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command(t_data *data)
{
	t_argv	*aux;
	char	**path;

	aux = *data->argv;
	path = ft_split(cmmd_find_path(data->myenv_str), ':');
	while (aux)
	{	
		aux->direction = cmmd_path(path, aux->split[0]);
		printf("dir->%s\n", aux->direction);
		if (aux->direction == NULL)
			aux->error_code = 127;
		else
			aux->error_code = 100;
		printf("error->%i\n", aux->error_code);
		aux = aux->next;
	}
/*
	while (arg[i])
	{
		printf("arg[%i]-> %s\n", i, arg[i]);
		i++;
	}
	i = 0;
	while (argv[i])
	{
		printf("argv[%i]-> %s\n", i, argv[i]);
		i++;
	}
	printf("dir-> %s\n", direction);
*/
/*
	if (direction == NULL)
		return (127);
*/
	aux = *data->argv;
	if (aux->error_code == 100)	
		aux->error_code = execute(data, aux->direction);
	
	free_env_char(path);
//	free(direction);
	return (aux->error_code);
}

int	execute(t_data *data, char *direction)
{
	int			fd;
	int			fd2;
	int			status;
	int			pid;
	t_argv		*arg;

	arg = *data->argv;
	pid = fork();
	fd = open(data->infile, O_RDONLY);
	if (fd < 0)
		return (0);
	fd2 = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd2 < 0)
		return (0);
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		if (execve(direction, arg->split, data->myenv_str) < 0)
			return (127);
			//exit (127);
	}
	close(fd);
	wait(&status);
	return (100);
}
