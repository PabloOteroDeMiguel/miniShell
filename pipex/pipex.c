/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:57:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/01/18 13:31:22 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	char	**arg1;
	char	**arg2;
	char	**direction;

	if (argc != 5)
		ft_argc(argc);
	else
	{
		direction = malloc(sizeof(char *) * 2);
		*direction = 0;
		arg1 = ft_split(argv[2], ' ');
		arg2 = ft_split(argv[3], ' ');
		path = ft_split(ft_find_path(envp), ':');
		direction[0] = ft_path(path, arg1[0]);
		direction[1] = ft_path(path, arg2[0]);
		ft_valid_direction(direction, argv);
		ft_pipex(argv, envp, direction);
	}
}
