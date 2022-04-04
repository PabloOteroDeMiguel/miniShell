/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:42:58 by potero-d          #+#    #+#             */
/*   Updated: 2022/04/04 11:40:27 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_myenv	*envnew(char *str)
{
	t_myenv	*element;

	element = malloc(sizeof(t_myenv));
	if (!element)
		return (NULL);
	element->key = str;
	element->value = getenv(str);
	element->next = NULL;
	return (element);
}

t_myenv	*envlast(t_myenv *myenv)
{
	t_myenv	*aux;

	aux = myenv;
	if (!myenv)
		return (0);
	while (aux->next != 0)
		aux = aux->next;
	return (aux);
}

void	env_add_back(t_myenv **myenv, t_myenv *new)
{
	t_myenv	*aux;

	if (*myenv)
	{
		aux = envlast(*myenv);
		aux->next = new;
	}
	else
		*myenv = new;
}

void	min_getenv(char **envp, t_myenv **myenv)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		env_add_back(myenv, envnew(ft_substr(envp[i], 0, j)));
		i++;
	}
}

void	print_env(t_myenv **myenv)
{
	t_myenv	*aux;
	int		i;

	i = 0;
	aux = *myenv;
	while (aux)
	{
		printf("%s=%s\n", aux->key, aux->value);
		aux = aux->next;
	}
}

