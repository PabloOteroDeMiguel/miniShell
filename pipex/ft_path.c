/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:29:07 by potero-d          #+#    #+#             */
/*   Updated: 2022/01/17 11:48:46 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 3) == 0)
			return (&envp[i][5]);
		i++;
	}
	return (0);
}

char	*ft_path(char **path, char *arg)
{
	int		i;
	char	*new_path;

	new_path = NULL;
	i = 0;
	while (path[i])
	{
		if (ft_addarg(&new_path, path[i], arg) == 0)
			return (new_path);
		free(new_path);
		i++;
	}
	ft_not_cmd(arg);
	new_path = 0;
	return (new_path);
}
