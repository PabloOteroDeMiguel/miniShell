/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:18:26 by potero-d          #+#    #+#             */
/*   Updated: 2021/09/23 12:32:48 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"

static	int	ft_cont(int n, int c)
{
	int	i;

	i = n;
	while ((i / 10) >= 1)
	{
		c++;
		i = i / 10;
	}
	return (c);
}

static char	*ft_str(char *str, int c, int n, int m)
{
	while (c > 0)
	{
		str[c] = (n % 10) + 48;
		n = n / 10;
		c--;
	}
	str[c] = n + 48;
	if (m == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		c;
	int		m;
	char	*str;

	c = 0;
	m = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		c++;
		n = -n ;
		m = 1;
	}
	c = ft_cont(n, c);
	str = malloc(sizeof(char) * (c + 2));
	if (!str)
		return (0);
	str[c + 1] = '\0';
	str = ft_str(str, c, n, m);
	return (str);
}
