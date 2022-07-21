/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:22:29 by potero            #+#    #+#             */
/*   Updated: 2022/07/21 14:52:19 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_myenv **myenv)
{
	int		i;
	t_myenv	*aux;

	i = 0;
	aux = *myenv;
	while (aux)
	{
		if (ft_strcmp(aux->key, "?") == 0)
			aux = aux->next;
		else
		{
			printf("%s=%s\n", aux->key, aux->value);
			aux = aux->next;
		}
	}
}

void	print_list(t_argv **argv)
{
	int		w;
	int		i;
	t_argv	*aux;

	w = 0;
	aux = *argv;
	while (aux)
	{
		i = 0;
		printf("arg[%d]->%s\n", w, aux->arg);
		while (aux->split[i])
		{
			printf("\ts[%d]->%s\n", i, aux->split[i]);
			i++;
		}
		w++;
		aux = aux->next;
	}
}
