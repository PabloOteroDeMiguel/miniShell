/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:02:11 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/03/23 17:01:18 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_pipex.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	if (n == 0 || dst == src)
		return (dst);
	while (i < n)
	{
		if (s1[i] != s2[i])
			s1[i] = s2[i];
		i++;
	}
	return (dst);
}
