/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:05:27 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/23 14:06:15 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aux2;

	if (s1 == 0 || s2 == 0)
		return (0);
	aux2 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (aux2 == 0)
		return (0);
	ft_memcpy(aux2, s1, ft_strlen(s1) + 1);
	ft_strlcat(aux2, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (aux2);
}
