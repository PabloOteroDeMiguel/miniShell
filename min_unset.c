/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:32:48 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/05 11:58:10 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_unset(t_data *data)
{
	aux_unset(data->myenv, *data->argv);
	free_env_char(data->myenv_str);
	data->myenv_str = env_to_char(data->myenv);
}

void	aux_unset(t_myenv **myenv, t_argv *argv)
{
	t_myenv	*aux;
	t_myenv	*aux2;
	int		i;

	i = 1;
	while (argv->split[i])
	{
		aux = *myenv;
		aux2 = *myenv;
		while (aux2->next)
		{
			if (ft_strcmp(argv->split[i], aux2->next->key) == 0)
			{
				aux = aux->next;
				free(aux->key);
				free(aux->value);
				aux2->next = aux->next;
				free(aux);
				break ;
			}
			aux = aux->next;
			aux2 = aux2->next;
		}
		i++;
	}
}
