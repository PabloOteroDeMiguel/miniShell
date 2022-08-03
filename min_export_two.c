/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_export_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:33:19 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/03 11:18:32 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_myenv	*export_just_new(char *str)
{
	t_myenv	*element;

	element = malloc(sizeof(t_myenv));
	if (!element)
		return (NULL);
	element->key = ft_strdup(str);
	element->value = 0;
	element->exp = 0;
	element->next = NULL;
	return (element);
}

int	just_exist_key(char *str, t_myenv *myenv)
{
	t_myenv	*aux;

	aux = myenv;
	while (aux)
	{
		if (ft_strcmp(aux->key, str) == 0)
			return (1);
		aux = aux->next;
	}
	return (0);
}

void	min_just_export(t_myenv *myenv)
{
	t_myenv	*aux;
	t_myenv	*aux2;
	int		cont;
	int		i;

	cont = cont_env(myenv);
	i = -1;
	aux = myenv;
	while (++i < cont - 1)
	{
		aux = myenv;
		while (aux->exp == 1)
			aux = aux->next;
		aux2 = aux->next;
		while (aux2 && i != cont - 1)
		{
			if (ft_strcmp(aux->key, aux2->key) > 0 && aux2->exp != 1) 
				aux = aux2;
			aux2 = aux2->next;
		}
		if (ft_strcmp(aux->key, "?") != 0)
		{
			if (aux->value == NULL)
				printf("declare -x %s\n", aux->key);
			else
				printf("declare -x %s=\"%s\"\n", aux->key, aux->value);
		}
		aux->exp = 1;
	}
	aux = myenv;
	while (aux)
	{
		if (aux->exp == 1)
			aux->exp = 0;
		else
		{
			if (aux->value == NULL)
				printf("declare -x %s\n", aux->key);
			else
				printf("declare -x %s=\"%s\"\n", aux->key, aux->value);
		}
		aux = aux->next;
	}
}
