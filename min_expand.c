/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:13:41 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/02 19:33:25 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*change_str(char *str, t_myenv **myenv)
{
	t_myenv	*aux;
	char	*key;
	char	*quote;
	char	*aux1;
	char	*print;
	char	*sub;
	int		i;

	aux = *myenv;
	quote = 0;
	key = ft_strchr(str, '$') + 1;
	i = 0;
	while (str[i] != '$')
		i++;
	sub = ft_substr(str, 0, i);
	if (ft_strchr(key, 39) != 0)
	{
		aux1= ft_strchr(key, 39);
		quote = ft_strdup(aux1);
		i = 0;
		while (key[i] != 39)
			i++;
		key[i] = 0;
	}
	while (aux)
	{
		if (ft_strcmp(key, aux->key) == 0)
		{
		//	printf("key->%s\n", key);
			aux1 = ft_strjoin(sub, aux->value);
		//	printf("aux->%s\n", aux1);
			free(sub);
			if (quote != 0)
				print = ft_strjoin(aux1, quote);
			else
				print = ft_strdup(aux1);
			free(aux1);
			free(quote);
		//	printf("pri->%s\n", print);
			return (print);
		}
		aux = aux->next;
	}
	print = ft_strjoin(sub, quote);
	free(quote);
	free(sub);
	return (print);
}
/*
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
*/

int	change(int i)
{
	if (i == 0)
		return(1);
	else
		return(0);
}
void	expand(t_data *data)
{
	t_argv	*argv;
	int		i;
	char	*aux;
	int		single_quote;
//	int		j;

	argv = *data->argv;
	while (argv)
	{
		single_quote = 0;
		i = 0;
		while (argv->arg[i])
		{	
			if (argv->arg[i] == 39)
				single_quote = change(single_quote);
			if (argv->arg[i] == '$' && single_quote == 0)
			{
				aux = change_str(argv->split[i], data->myenv);
				if (aux != 0)
				{	
					free(argv->arg);
					argv->arg = ft_strdup(aux);
					free(aux);
				}
	/*
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
	*/
			}	
			i++;
		}
		argv = argv->next;
	}
}
