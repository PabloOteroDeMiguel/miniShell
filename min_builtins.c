/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:13:18 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/01 10:21:28 by potero           ###   ########.fr       */
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
	return (0);
}

void	min_echo(t_argv **argv)
{
	t_argv	*aux;
//	char	*print;
	int		i;
	int		n;

	n = 0;
	aux = *argv;
	if (aux->split[1])
	{
		if (check_flags(aux->split[1]) == 0)
		{
			n = 1;
			i = 2;
		}
		else
			i = 1;
		while (aux->split[i])
		{
			printf("%s", aux->split[i]);
			i++;
			if (aux->split[i] != 0)
				printf(" ");
		}
		aux = aux->next;
		while (aux)
		{
			i = 0;
			while (aux->split[i])
			{
				printf("%s", aux->split[i]);
				i++;
				if (aux->split[i] != 0)
					printf(" ");
			}
			if (aux->next != 0)
				printf(" ");
			aux = aux->next;
		}
	}
	else
	{
		aux = aux->next;
		if (aux && check_flags(aux->split[1]) == 0)
		{
			n = 1;
			aux = aux->next;
		}
		while (aux)
		{
			i = 0;
			while (aux->split[i])
			{
				printf("%s", aux->split[i]);
				i++;
				if (aux->split[i] != 0)
					printf(" ");
			}	
			if (aux->next != 0)
				printf(" ");
			aux = aux->next;
		}
	}
	if (n == 0)
		printf("\n");
}

void	min_pwd(t_myenv	**myenv)
{
	t_myenv	*aux;

	aux = *myenv;
	while (ft_strcmp(aux->key, "PWD") != 0)
		aux = aux->next;
	printf("%s\n", aux->value);
}
