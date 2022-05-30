/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:20:12 by potero            #+#    #+#             */
/*   Updated: 2022/05/30 12:16:29 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command(t_data *data)
{
	t_argv	*arg;
	char	**path;
	char	*direction;

	arg = *data->argv;
	path = ft_split(cmmd_find_path(data->myenv_str), ':');
	direction = cmmd_path(path, arg->split[0]);

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
	printf("dir-> %s\n", direction);*/
	if (direction == NULL)
		return (127);
	arg->error_code = execute(data, direction);
	
	free_env_char(path);
	free(direction);
	return (arg->error_code);
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
