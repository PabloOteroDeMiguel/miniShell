/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_remove_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:01:20 by potero            #+#    #+#             */
/*   Updated: 2022/06/09 18:52:46 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotes(char *str, char c)
{
	char	*ret;
	char	*aux;
	char	*aux2;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 34) || (str[i] == 39))
		{
			c = str[i];
			aux = ft_substr(str, 0, i);
			j = i + 1;
			while (str[j] && str[j] != c)
				j++;
			aux2 = ft_substr(str, i + 1, j - i - 1);
			ret = ft_strjoin(aux, aux2);
			free(aux);
			free(aux2);
			aux = ft_substr(str, j + 1, ft_strlen(str) - j);
			aux2 = ft_strjoin(ret, aux);
			free(str);
			str = ft_strdup(aux2);
			i = j - 2;
		}
		i++;
	}
	return (aux2);
}

void	remove_quotes(t_argv **argv)
{
	int		i;
	char	c;
	char	*str;
	t_argv	*aux;

	aux = *argv;
	c = 0;
	while (aux)
	{
		i = 0;
		if (ft_strchr(aux->arg, 34) != 0
			|| ft_strchr(aux->arg, 39) != 0)
		{	
			str = quotes(aux->arg, c);
			free(aux->arg);
			aux->arg = ft_strdup(str);
			free(str);
		}
		while (aux->split[i])
		{
			if (ft_strchr(aux->split[i], 34) != 0
				|| ft_strchr(aux->split[i], 39) != 0)
			{
				str = quotes(aux->split[i], c);
				free(aux->split[i]);
				aux->split[i] = ft_strdup(str);
				free(str);
			}
			i++;
		}
		aux = aux->next;
	}		
}
