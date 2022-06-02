/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:57:16 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/29 09:57:48 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_comm_path	*ft_lstnew(char **content)
{
	t_comm_path	*lista;

	lista = malloc(sizeof(t_comm_path));
	if (lista == 0)
		return (0);
	lista->comm = content;
	lista->ok = 1;
	lista->next = NULL;
	return (lista);
}

t_comm_path	*ft_lstnew_error(char **content)
{
	t_comm_path	*lista;

	lista = malloc(sizeof(t_comm_path));
	if (lista == 0)
		return (0);
	lista->comm = content;
	lista->ok = 0;
	lista->next = NULL;
	return (lista);
}
