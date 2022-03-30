/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:13:18 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/30 12:38:22 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_echo(t_argv **argv)
{
	t_argv	*aux;
	
	aux = *argv;
	printf("1\n");
	printf("aux-%s\n", aux->arg);
	if ((ft_strcmp(aux->arg, "echo -n ") == 0) ||
			(ft_strcmp(aux->arg, "ECHO -n ") == 0))
	{
		//aux = aux->next;
		while (aux)
		{
			printf("%s", aux->arg);
			aux = aux->next;
		}
		return ;
	}
	else
		//aux = aux->next;
	if	(ft_strcmp(aux->next->arg, "-n") == 0)
	{
		aux = aux->next;
		while (aux)
		{
			printf("%s", aux->arg);
			aux = aux->next;
		}
		return;
	}
	printf("2\n");
/*	else
	{
		printf("3\n");
		aux = *argv;
		while (aux)
		{
			printf("%s", aux->arg);
			aux = aux->next;
		}
		printf("\n");
	}*/
}

