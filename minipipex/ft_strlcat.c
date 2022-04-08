/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:36:48 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/03/23 17:01:53 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_pipex.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	pos[3];

	pos[0] = 0;
	pos[1] = ft_strlen(dst);
	pos[2] = ft_strlen(dst);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (pos[2] >= dstsize)
		return (dstsize + ft_strlen(src));
	while (pos[1] < (dstsize - 1) && src[pos[0]])
	{
		dst[pos[1]] = src[pos[0]];
		pos[0]++;
		pos[1]++;
	}
	dst[pos[1]] = '\0';
	return (pos[2] + ft_strlen(src));
}
