/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:13:41 by potero-d          #+#    #+#             */
/*   Updated: 2022/04/08 14:41:40 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_str(char *str, t_myenv **myenv)
{
	t_myenv	*aux;
	char	*key;
	char	*print;
	char	*sub;
	int		i;

	aux = *myenv;
	key = ft_strchr(str, '$') + 1;
	i = 0;
	while (str[i] != '$')
		i++;
	sub = ft_substr(str, 0, i);
	while (aux)
	{
		if (ft_strcmp(key, aux->key) == 0)
		{
			print = ft_strjoin(sub, aux->value);
			free(sub);
			return (print);
		}
		aux = aux->next;
	}
	free(sub);
	return (0);
}

void	expand(t_data *data)
{
	t_argv	*argv;
	int		i;
	char	*aux;
	int		j;

	argv = *data->argv;

	while (argv)
	{
		i = 0;
		while (argv->split[i])
		{
			if (ft_strchr(argv->split[i], '$') != 0 && argv->quote != 1)
			{
				aux = change_str(argv->split[i], data->myenv);
				if (aux != 0)
				{	
					free(argv->split[i]);
					argv->split[i] = ft_strdup(aux);
					free(aux);
				}
				else
				{
					j = i;
					while (argv->split[j + 1])
					{
						free(argv->split[j]);
						argv->split[j] = ft_strdup(argv->split[j + 1]);
						j++;
					}
					free(argv->split[j]);
					argv->split[j] = 0;
				}
				i--;
			}	
			i++;
		}
		argv = argv->next;
	}
}
