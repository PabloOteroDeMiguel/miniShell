/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:13:18 by potero-d          #+#    #+#             */
/*   Updated: 2022/04/04 10:15:06 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_echo(t_argv **argv)
{
	t_argv	*aux;
	int		i;
	int		n;
	
	n = 0;
	aux = *argv;
	if (aux->split[1])
	{
		if (ft_strcmp(aux->split[1], "-n") == 0)
		{
			n = 1;
			i = 2;
		}
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
	else
	{
		aux = aux->next;
		if (aux && (ft_strcmp(aux->arg, "-n") == 0))
		{
			n = 1;
			aux = aux->next;
		}
		while (aux)
		{
			printf("%s", aux->arg);
			aux = aux->next;
		}
	}
	if (n == 0)
		printf("\n");
}

void	min_pwd(t_myenv	**myenv)
{
	t_myenv	*aux;

	aux = *myenv;
	while (ft_strcmp(aux->key, "PWD") != 0)
		aux = aux->next;
	printf("%s\n", aux->value);
}

