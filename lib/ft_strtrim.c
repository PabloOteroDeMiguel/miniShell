/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 13:49:05 by potero-d          #+#    #+#             */
/*   Updated: 2021/09/26 11:54:49 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !set)
		return (0);
	i = 0;
	j = ft_strlen(s1);
	if (ft_strlen(s1) == 0 || ft_strlen(set) == 0)
	{
		str = ft_strdup(s1);
		if (!str)
			return (0);
		return (str);
	}
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > i && ft_strrchr(set, s1[j]))
		j--;
	str = ft_substr((char *)s1, i, j - i + 1);
	if (!str)
		return (0);
	return (str);
}
