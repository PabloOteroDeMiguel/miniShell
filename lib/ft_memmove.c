/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 09:24:47 by potero-d          #+#    #+#             */
/*   Updated: 2021/09/20 14:47:00 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*s1;
	char	*s2;

	s1 = (char *)dst;
	s2 = (char *)src;
	i = 0;
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			s1[len] = s2[len];
		}
	}
	while (i < len)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dst);
}
