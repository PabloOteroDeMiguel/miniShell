/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_export_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:33:19 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/04 11:57:52 by potero-d         ###   ########.fr       */
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

static void	print_export(t_myenv *aux)
{
	if (aux->value == NULL)
		printf("declare -x %s\n", aux->key);
	else
		printf("declare -x %s=\"%s\"\n", aux->key, aux->value);
}

static void	aux_just_export(int cont, t_myenv *myenv)
{
	t_myenv	*aux;
	t_myenv	*aux2;
	int		i;

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
			print_export(aux);
		aux->exp = 1;
	}
}

void	min_just_export(t_myenv *myenv)
{
	t_myenv	*aux;
	int		cont;

	cont = cont_env(myenv);
	aux_just_export(cont, myenv);
	aux = myenv;
	while (aux)
	{
		if (aux->exp == 1)
			aux->exp = 0;
		else
			print_export(aux);
		aux = aux->next;
	}
}
