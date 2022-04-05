/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:32:48 by potero-d          #+#    #+#             */
/*   Updated: 2022/04/05 13:38:45 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_unset(t_data *data)
{
//	t_myenv	**myenv;
	t_myenv	*aux;
	t_myenv	*aux2;
	t_argv	*argv;
	int		i;

	argv = *data->argv;
	//myenv = data->myenv;
	i = 1;
	while (argv->split[i])
	{
	//	aux = *myenv;
		aux = *data->myenv;
		while (aux)
		{
			if (ft_strcmp(argv->split[i], aux->key) == 0)
			{
				free(aux->key);
				free(aux->value);
				aux2 = aux->next;
				free(aux);
				aux = aux2;
			}
			if (aux)
				aux = aux->next;
		}
		i++;
	}
	if (argv->next != 0)
	{
		argv = argv->next;
		while (argv)
		{
			i = 0;
			while (argv->split[i])
			{
				//aux = *myenv;
				aux = *data->myenv;
				while (aux)
				{
					if (ft_strcmp(argv->split[i], aux->key) == 0)
					{
						free(aux->key);
						free(aux->value);
						aux2 = aux->next;
						free(aux);
						aux = aux2;
					}
					if (aux)
						aux = aux->next;
				}
				i++;
			}
		}
	}
}
