/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:10:30 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/31 11:21:07 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words(char const *s, char c)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	if (s[i] == c)
		i++;
	word++;
	while (s[i + 1])
	{
		if (s[i] == c && s[i + 1] != c)
			word++;
		i++;
	}
	return (word);
}

void static	ft_aux(char ***str, char const *s, char c)
{	
	int	i;
	int	j;
	int	w;

	i = 0;
	j = 0;
	w = 0;
	while (s[i])
	{
		if ((s[i] == c))
		{	
			(*str)[w] = ft_substr(s, i - j, j);
			while (s[i + 1] == c)
				i++;
			w++;
			j = 0;
		}
		else if (s[i] != c)
			j++;
		i++;
	}
	if (s[i - 1] != c)
		(*str)[w++] = ft_substr(s, i - j, j);
	(*str)[w] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (0);
	if (ft_strlen(s) == 0)
	{
		str = malloc(sizeof(char *) * (1));
		str[0] = 0;
		return (str);
	}
	str = malloc(sizeof(char *) * (words(s, c) + 1));
	if (!str)
		return (0);
	while (*s == c)
		s++;
	ft_aux(&str, s, c);
	return (str);
}
