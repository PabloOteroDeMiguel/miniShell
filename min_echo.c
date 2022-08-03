/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:13:18 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/02 18:50:09 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flags(char *flag)
{
	int	i;
	int	len;

	i = 0;
	if (flag[i] == '-')
	{
		i++;
		len = ft_strlen(flag);
		while (i < len)
		{
			if (flag[i] != 'n')
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

void	min_echo(t_argv **argv)
{
	t_argv	*aux;
	int		i;
	int		n;

	n = 0;
	aux = *argv;
	i = 1;
	if (aux->split[i])
	{
		while (check_flags(aux->split[i]) == 0)
		{
			n = 1;
			i++;
		}
		while (aux->split[i])
		{
			printf("%s", aux->split[i]);
			i++;
			if (aux->split[i] != 0)
				printf(" ");
		}
	}
	if (n == 0)
		printf("\n");
}
