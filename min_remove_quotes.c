/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_remove_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:01:20 by potero            #+#    #+#             */
/*   Updated: 2022/07/05 15:20:45 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	aux_strings(char **str, int i)
{
	char	*aux;
	char	*aux2;

	aux = ft_substr(*str, 0, i);
	aux2 = ft_substr(*str, i + 1, ft_strlen(*str) - i);
	free(*str);
	*str = ft_strjoin(aux, aux2);
	free(aux);
	free(aux2);
}

char	*quotes(char *arg)
{
	int		i;
	char	c;
	char	*ret;
	char	*str;

	str = ft_strdup(arg);
	i = 0;
	while (str[i])
	{
		if ((str[i] == 34) || (str[i] == 39))
		{
			c = str[i];
			aux_strings(&str, i);
			while (str[i] && str[i] != c)
				i++;
			aux_strings(&str, i);
		}
		i++;
	}
	free(str);
	ret = ft_strdup(str);
	return (ret);
}

static void	aux_split(char **split)
{
	char	*str;

	str = quotes(*split);
	free(*split);
	*split = ft_strdup(str);
	free(str);
}

void	remove_quotes(t_argv **argv)
{
	int		i;
	char	*str;
	t_argv	*aux;

	aux = *argv;
	while (aux)
	{
		i = 0;
		if (ft_strchr(aux->arg, 34) != 0
			|| ft_strchr(aux->arg, 39) != 0)
		{	
			str = quotes(aux->arg);
			free(aux->arg);
			aux->arg = str;
		}
		while (aux->split[i])
		{
			if (ft_strchr(aux->split[i], 34) != 0
				|| ft_strchr(aux->split[i], 39) != 0)
				aux_split(&aux->split[i]);
			i++;
		}
		aux = aux->next;
	}		
}
