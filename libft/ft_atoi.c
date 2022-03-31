/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:48:23 by potero-d          #+#    #+#             */
/*   Updated: 2021/09/21 08:54:09 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_num(unsigned long long n, int c)
{
	if (n > 9223372036854775807 && c == -1)
		return (0);
	if (n > 9223372036854775807 && c == 1)
		return (-1);
	return (n * c);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	n;
	int					c;

	i = 0;
	while ((str[i] == ' ') || ((str[i] > 8) && (str[i] < 14 )))
		i++;
	c = 1;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			c = -1;
		i++;
	}
	n = 0;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		n = (n * 10) + (str[i] - 48);
		i++;
	}
	return (ft_num(n, c));
}
