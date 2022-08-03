/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmmd_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:27:12 by potero            #+#    #+#             */
/*   Updated: 2022/08/03 12:08:27 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmmd_addarg(char **new_path, char *path, char *arg)
{
	char	*aux;
	int		ac;

	ac = access(arg, X_OK);
	if (ac == 0)
	{
		*new_path = ft_strdup(arg);
		return (0);
	}
	aux = ft_strjoin(path, "/");
	*new_path = ft_strjoin(aux, arg);
	ac = access(*new_path, X_OK);
	free(aux);
	if (ac == 0)
		return (0);
	else
		return (1);
}

void	not_cmmd(char *str)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
}

char	*cmmd_find_path(char **envp)
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

char	*cmmd_path(char **path, char *arg)
{
	int		i;
	char	*new_path;

	if (path == 0)
	{
		i = access(arg, X_OK);
		if (i  == 0)
		{
			new_path = ft_strdup(arg);
			return (new_path);
		}
		else
			return (0);
	}
	new_path = NULL;
	i = 0;
	while (path[i])
	{
		if (cmmd_addarg(&new_path, path[i], arg) == 0)
			return (new_path);
		free(new_path);
		i++;
	}
	if (path == 0)
	{
		i = access(arg, X_OK);
		if (i  == 0)
			new_path = ft_strdup(arg);
	}
	new_path = 0;
	return (new_path);
}
