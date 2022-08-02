/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_export_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:33:19 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/02 17:19:03 by potero-d         ###   ########.fr       */
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
	printf("cont->%d\n", cont);
	i = 0;
	while (i++ < cont - 1)
	{
		aux = myenv;
	//	printf("key->%s\n", aux->key);
	//	printf("exp->%d\n", aux->exp);
		while (aux->exp == 1)
			aux = aux->next;
		aux2 = aux->next;
	//	printf("aqui\n");
		while (aux2->next && i != cont - 1)
		{
			while (aux2->exp == 1)
				aux2 = aux2->next;
			if (ft_strcmp(aux->key, aux2->key) < 0)
				aux2 = aux2->next;
			else
			{
				aux = aux2;
				aux2 = aux2->next;
			}
		}
		if (ft_strcmp(aux->key, "?") != 0 && ft_strcmp(aux->key, "_") != 0)
			printf("declare -x %s=\"%s\"\n", aux->key, aux->value);
		aux->exp = 1;
	}
	aux = myenv;
	while (aux)
	{
		aux->exp = 0;
		aux = aux->next;
	}
}
