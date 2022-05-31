/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:10:04 by potero-d          #+#    #+#             */
/*   Updated: 2022/01/17 13:26:15 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_addarg(char	**new_path, char *path, char *arg)
{
	char	*aux;
	int		ac;

	ac = access(arg, X_OK);
	if (ac == 0)
	{
		*new_path = arg;
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
