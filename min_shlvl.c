/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 10:14:13 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/30 11:12:44 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl(t_myenv **myenv)
{
	int		i;
	t_myenv	*aux;

	aux = *myenv;
	while (aux)
	{
		if (ft_strcmp(aux->key, "SHLVL") == 0)
		{
			i = ft_atoi(aux->value);
			i++;
			printf("shlvl->%i\n", aux->shlvl);
			aux->shlvl++;
			printf("shlvl->%i\n", aux->shlvl);
			free(aux->value);
			aux->value = ft_itoa(i);
			break ;
		}
		aux = aux->next;
	}
}
