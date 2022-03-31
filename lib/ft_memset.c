/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:00:05 by potero-d          #+#    #+#             */
/*   Updated: 2021/09/14 12:51:36 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string.h>

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;
	char	*p;

	c = (unsigned char)c;
	i = 0;
	p = (char *)str;
	while (i < len)
	{
		p[i] = c;
		i++;
	}
	return (str);
}
