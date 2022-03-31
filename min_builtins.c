/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:13:18 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/31 11:38:53 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_echo(t_argv **argv)
{
	t_argv	*aux;
	int		i;
	
	aux = *argv;
	if	(ft_strcmp(aux->split[0], "echo") == 0)
	{
		if (aux->split[1])
		{
			if (ft_strcmp(aux->split[1], "-n") == 0)
				i = 2;
			else
				i = 1;
			while (aux->split[i])
			{
				printf("%s ", aux->split[i]);
				i++;
			}
			aux = aux->next;
			while (aux)
			{
				printf("%s", aux->arg);
				aux = aux->next;
			}
		}
	}

}

