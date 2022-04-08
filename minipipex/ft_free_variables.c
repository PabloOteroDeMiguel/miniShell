/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:36:06 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/03/23 17:01:01 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_pipex.h"

void	free_variables(t_comm_path **comm_dir)
{
	t_comm_path	*aux;

	aux = *comm_dir;
	while (*comm_dir)
	{
		aux = (*comm_dir)->next;
		if ((*comm_dir)->comm != NULL)
			free_variables_list((*comm_dir)->comm);
		free(*comm_dir);
		*comm_dir = aux;
	}
	free(*comm_dir);
}

void	free_variables_list(char **list)
{
	int		i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}
