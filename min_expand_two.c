/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expand_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:43:38 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/01 12:48:49 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*change_aux(t_myenv **myenv, int *len, char *key, char *extra)
{
	t_myenv	*env;
	char	*print;
	char	*aux;

	env = *myenv;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			aux = ft_strdup(env->value);
			*len = ft_strlen(aux);
			if (extra)
			{
				print = ft_strjoin(aux, extra);
				free(extra);
			}
			else
				print = ft_strdup(aux);
			free(aux);
			return (print);
		}
		env = env->next;
	}
	return (0);
}

static char	*change_aux_two(char *extra)
{
	char	*print;

	if (extra == 0)
	{
		print = malloc(sizeof(char *) * 1);
		print[0] = 0;
	}
	else
		print = ft_strdup(extra);
	return (print);
}

char	*change_str(char *str, t_myenv **myenv, int *len)
{
	char	*key;
	char	*extra;
	char	*print;
	int		i;

	extra = 0;
	key = ft_strchr(str, '$') + 1;
	i = 0;
	while (key[i])
	{
		if (key[i] == 39 || key[i] == 34 || key[i] == '$' || key[i] == ' ')
		{
			extra = ft_strdup(ft_strchr(key, key[i]));
			key[i] = 0;
			break ;
		}
		i++;
	}
	print = change_aux(myenv, len, key, extra);
	if (print == 0)
		print = change_aux_two(extra);
	return (print);
}
