/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:43:34 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/12 12:11:42 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_comm_path **lst, t_comm_path *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
		ft_lstlast(*lst)->next = new;
}
