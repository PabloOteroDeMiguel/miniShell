/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:44:20 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/20 14:32:47 by potero-d         ###   ########.fr       */
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

void	min_export(t_data *data)
{
	t_myenv	*myenv;
	t_argv	*argv;
	int		i;

	i = 1;
	myenv = *data->myenv;
	argv = *data->argv;
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
