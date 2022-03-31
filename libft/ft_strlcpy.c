/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 09:28:36 by potero-d          #+#    #+#             */
/*   Updated: 2021/09/20 14:49:01 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string.h>

size_t	ft_strlen(const char *str);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	unsigned char	*dst1;
	unsigned char	*src1;

	i = 0;
	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize > 0)
	{	
		while ((i < dstsize - 1) && (i < ft_strlen(src)))
		{
			dst1[i] = src1[i];
			i++;
		}
		dst1[i] = '\0';
	}
	return (ft_strlen(src));
}
