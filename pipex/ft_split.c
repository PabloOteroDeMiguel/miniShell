/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 10:34:46 by pmoreno-          #+#    #+#             */
/*   Updated: 2021/09/23 10:38:02 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_fullchars(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
			return (0);
		i++;
	}
	return (1);
}

static size_t	ft_countln(char const *s, char c)
{
	size_t	l;
	size_t	car;

	l = 0;
	car = 1;
	if (ft_strchr(s, c) == 0)
		return (1);
	if (ft_fullchars(s, c))
		return (0);
	if (s[0] != c)
		l++;
	while (car < ft_strlen(s))
	{
		if (s[car] != c && s[car - 1] == c)
			l++;
		else if (car == (ft_strlen(s) - 1) && s[car] != c && s[car - 1] == c)
			l++;
		car++;
	}
	return (l);
}

static size_t	ft_separator(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] == c && i < ft_strlen(s))
		i++;
	return (i);
}

static void	ft_array(char **str, char const *s, char c, size_t p[2][3])
{
	if (s[p[0][0]] != c)
		p[1][1]++;
	if ((s[p[0][0]] == c || p[0][0] == (ft_strlen(s) - 1)) && p[1][1] > 0)
	{
		str[p[1][2]] = malloc(sizeof(char) * (p[1][1] + 1));
		if (p[1][0] == 1)
			ft_strlcpy(str[p[1][2]], &s[p[0][1]], p[1][1] + 1);
		else
		{
			if (p[0][0] == (ft_strlen(s) - 1) && s[p[0][0]] != c)
				ft_strlcpy(str[p[1][2]], &s[p[0][0] - p[1][1] + 1],
					p[1][1] + 1);
			else
				ft_strlcpy(str[p[1][2]], &s[p[0][0] - p[1][1]], p[1][1] + 1);
		}
		p[1][1] = 0;
		p[1][2]++;
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	p[2][3];
	char	**str;

	if (s == 0)
		return (0);
	p[0][0] = 0;
	p[0][1] = ft_separator(s, c);
	p[1][0] = ft_countln(s, c);
	p[1][1] = 0;
	p[1][2] = 0;
	str = malloc(sizeof(char *) * (p[1][0] + 1));
	if (str == 0)
		return (0);
	p[0][0] = ft_separator(s, c);
	while (p[0][0] < ft_strlen(s) && p[1][2] < p[1][0])
	{
		ft_array(str, s, c, p);
		p[0][0]++;
	}
	str[p[1][2]] = 0;
	return (str);
	free(str);
}
