/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:44:20 by potero-d          #+#    #+#             */
/*   Updated: 2022/04/04 14:03:17 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_myenv *export_new(char *str)
{
	int		i;
	char	*aux;
	t_myenv	*element;

	element = malloc(sizeof(t_myenv));
	if (!element)
		return (NULL);
	i = 0;
	aux = ft_strchr(str, '=');
	if (aux != 0)
	{
		while (str[i] != '=')
			i++;
		element->key = ft_substr(str, 0, i);
		element->value = aux;
		element->next = NULL;
	}
	else
		return (NULL);
	return (element);
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
		env_add_back(&myenv, export_new(argv->split[i]));
		i++;
	}
	if (argv->next != 0)
		argv = argv->next;
	while (argv)
	{
		i = 0;
		while (argv->split[i])
		{
			env_add_back(&myenv, export_new(argv->split[i]));
			i++;
		}
		argv = argv->next;
	}
}
