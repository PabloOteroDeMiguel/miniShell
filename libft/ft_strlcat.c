/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 09:46:50 by potero-d          #+#    #+#             */
/*   Updated: 2021/09/21 08:53:00 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	z;

	z = ft_strlen(dst);
	j = ft_strlen(dst);
	i = 0;
	if ((z < dstsize - 1) && dstsize > 0)
	{
		while ((j < dstsize - 1) && (src[i] != '\0'))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	if (z >= dstsize)
		z = dstsize;
	return (z + ft_strlen(src));
}
