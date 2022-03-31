/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 09:22:20 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/31 10:37:59 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<string.h>
#include"libft.h"

char	*ft_strnstr(const char *str, const char *nstr, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (nstr[0] == '\0')
		return ((char *)(str));
	while ((i < len) && (str[i] != '\0'))
	{
		if (nstr[j] == str[i])
		{
			j++;
			if (j == ft_strlen(nstr))
				return ((char *)(&str[i - j + 1]));
		}
		else
		{
			i = i - j;
			j = 0;
		}
		i++;
	}
	return (0);
}
