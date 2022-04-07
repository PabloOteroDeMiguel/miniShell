/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:31:47 by potero            #+#    #+#             */
/*   Updated: 2022/04/07 11:05:59 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_argv	*lstnew(char *str, int q)
{
	t_argv	*element;

	element = malloc(sizeof(t_argv));
	if (!element)
		return (NULL);
	element->arg = str;
	element->quote = q;
	element->next = NULL;
	return (element);
}

int	lstsize(t_argv *argv)
{
	int		i;
	t_argv	*aux;

	i = 0;
	if (!argv)
		return (0);
	aux = argv;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

t_argv	*lstlast(t_argv *argv)
{
	t_argv	*aux;

	aux = argv;
	if (!argv)
		return (0);
	while (aux->next != 0)
		aux = aux->next;
	return (aux);
}

void	lst_add_back(t_argv **argv, t_argv *new)
{
	t_argv	*aux;

	if (*argv)
	{
		aux = lstlast(*argv);
		aux->next = new;
	}
	else
		*argv = new;
}

void	add_front(t_argv **argv, t_argv *new)
{
	if (new)
	{
		new->next = *argv;
		*argv = new;
	}
}
