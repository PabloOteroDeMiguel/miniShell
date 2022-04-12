/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:57:16 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/12 12:18:31 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
