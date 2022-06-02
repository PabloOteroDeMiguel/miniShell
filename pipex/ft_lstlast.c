/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:51:52 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/29 09:52:22 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_lstsize(t_comm_path *lst)
{
	int			i;
	t_comm_path	*s;

	if (lst == NULL)
		return (0);
	i = 0;
	s = lst;
	while (s != NULL)
	{
		i++;
		s = s->next;
	}
	return (i);
}

t_comm_path	*ft_lstlast(t_comm_path *lst)
{
	int			i;
	t_comm_path	*ant;
	t_comm_path	*sig;

	if (lst == 0)
		return (0);
	i = 0;
	ant = lst;
	if (ft_lstsize(lst) > 1)
	{
		sig = lst->next;
		while (sig != NULL)
		{
			ant = sig;
			sig = sig->next;
		}
	}
	return (ant);
}
