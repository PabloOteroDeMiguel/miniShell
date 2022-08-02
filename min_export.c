/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:44:20 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/02 16:28:07 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_myenv	*export_new(char *str)
{
	int		i;
	char	*aux;
	t_myenv	*element;

	element = malloc(sizeof(t_myenv));
	if (!element)
		return (NULL);
	i = 0;
	aux = ft_strchr(str, '=') + 1;
	if (aux != 0)
	{
		while (str[i] != '=')
			i++;
		element->key = ft_substr(str, 0, i);
		element->value = (ft_strdup(aux));
		element->exp = 0;
		element->next = NULL;
	}
	else
		return (NULL);
	return (element);
}

int	exist_key(char *str, t_myenv *myenv)
{
	t_myenv	*aux;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	value = ft_strchr(str, '=') + 1;
	aux = myenv;
	while (aux)
	{
		if (ft_strcmp(aux->key, key) == 0)
		{
			aux->value = (ft_strdup(value));
			free(key);
			return (1);
		}
		aux = aux->next;
	}
	free(key);
	return (0);
}

int cont_env(t_myenv *myenv)
{
	t_myenv *aux;
	int		i;

	i = 0;
	aux = myenv;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
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
		while (aux->exp == 1)
			aux = aux->next;
		aux2 = aux->next;
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
}

void	min_export(t_data *data)
{
	t_myenv	*myenv;
	t_argv	*argv;
	int		i;

	i = 1;
	myenv = *data->myenv;
	argv = *data->argv;
	if (argv->split[1] == 0)
		min_just_export(myenv);

	while (argv->split[i])
	{
		if (ft_strchr(argv->split[i], '=') != 0)
		{
			if (exist_key(argv->split[i], myenv) == 0)
				env_add_back(&myenv, export_new(argv->split[i]));
		}
		i++;
	}
	free_env_char(data->myenv_str);
	data->myenv_str = env_to_char(data->myenv);
}
