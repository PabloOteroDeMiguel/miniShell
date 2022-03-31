/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:32:01 by potero-d          #+#    #+#             */
/*   Updated: 2021/09/20 11:34:12 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string.h>

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	p;
	unsigned char	*s;

	i = 0;
	p = c;
	s = (unsigned char *)str;
	while (i < n)
	{
		if (s[i] == p)
			return ((void *)(&str[i]));
		i++;
	}
	return (0);
}
