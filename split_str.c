/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:12:27 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/06/04 15:20:31 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_all_alphanumeric(const char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if ((str[i] < 65 || str[i] > 90 ) && (str[i] < 97 || str[i] > 122))
			return (i);
		i++;
	}
	return (-1);
}
