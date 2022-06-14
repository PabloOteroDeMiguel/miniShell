/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:13:18 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/04 15:19:57 by pmoreno-         ###   ########.fr       */
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

void	min_echo(t_argv **argv, t_myenv **env, int	error_code)
{
	t_argv	*aux;
	// char	**list;
	int		i;
	int		n;

	n = 0;
	aux = *argv;
	env = 0;
	printf("%d\n-------\n", error_code);
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
			printf("\n--------------> ARG %d", i);
			char *str = ft_strchr(aux->split[i], '$');
			printf("\n--------------> SPLIT: %s\n", str);
			if (!str)
			{
				printf("%s", aux->split[i]);
				if (aux->split[i] != 0)
					printf(" ");
			}
			else
			{
				int pos = ft_all_alphanumeric(str);
				printf("POS: %d\n", pos);
			}
			i++;
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
