/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:13:41 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/03 13:31:36 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*change_str(char *str, t_myenv **myenv , int *len)
{
	t_myenv	*aux;
	char	*key;
	char	*extra;
	char	*aux1;
	char	*print;
	int		i;

	aux = *myenv;
	extra = 0;
	key = ft_strchr(str, '$') + 1;
	printf("key->%s\n", key);
	i = 0;
	while (key[i])
	{
		if (key[i] == 39)
		{
			aux1 = ft_strchr(key, 39);
			extra = ft_strdup(aux1);
			key[i] = 0;
			break ;
		}
		else if (key[i] == 34)
		{
			aux1 = ft_strchr(key, 34);
			extra = ft_strdup(aux1);
			key[i] = 0;
			break ;
		}
		else if (key[i] == '$')
		{
			aux1 = ft_strchr(key, '$');
			extra = ft_strdup(aux1);
			key[i] = 0;
			break ;
		}
		else if (key[i] == ' ')
		{
			aux1 = ft_strchr(key, ' ');
			extra = ft_strdup(aux1);
			key[i] = 0;
			break ;
		}

		i++;
	}
	
	while (aux)
	{
		if (ft_strcmp(key, aux->key) == 0)
		{
		//	printf("key->%s\n", key);
		//	aux1 = ft_strjoin(sub, aux->value);
			aux1 = ft_strdup(aux->value);
			*len = ft_strlen(aux1);
		//	printf("aux->%s\n", aux1);
		//	free(sub);
			if (extra != 0)
				print = ft_strjoin(aux1, extra);
			else
				print = ft_strdup(aux1);
			free(aux1);
			free(extra);
		//	printf("pri->%s\n", print);
			return (print);
		}
		aux = aux->next;
	}
	if (extra == 0)
		{
			print = malloc(sizeof(char *) * 1);
			print[0] = 0;
		}
	else
		print = ft_strdup(extra);
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

int	change(int i, char c)
{
	int	ret;

	ret = 0;
	if ((i == 0) && (c == 34))
		ret = 2;
	else if ((i == 0) && (c == 39))
		ret = 1;
	else if( (i == 1) && (c == 34))
		ret = 1;
	else if ((i == 1) && (c == 39))
		ret = 0;
	else if ((i == 2) && (c == 34))
		ret = 0;
	else if ((i == 2) && (c == 39))
		ret = 2;
		return(ret);
}
void	expand(t_data *data)
{
	t_argv	*argv;
	int		i;
	int		len;
	char	*aux;
	char	*new;
	char	*prev;
	int		single_quote;
//	int		j;

	argv = *data->argv;
	while (argv)
	{
		single_quote = 0;
		i = 0;
		len = 0;
		while (argv->arg[i])
		{		
		//	printf("quote->%i\n", single_quote);
		//	printf("char[%i]->%c\n", i, argv->arg[i]);
			if ((argv->arg[i] == 39) || (argv->arg[i] == 34))
				single_quote = change(single_quote, argv->arg[i]);
		//	printf("quote->%i\n", single_quote);
			if (argv->arg[i] == '$' && single_quote != 1)
			{
				prev = ft_substr(argv->arg, 0, i);
		//		printf("prev->%s\n", prev);
				//aux = change_str(argv->split[i], data->myenv);
				aux = change_str(&argv->arg[i], data->myenv, &len);
				printf("prev->%s\n", prev);
				printf("aux->%s\n", aux);
		/*
				if (aux)
					len = ft_strlen(aux);
				else
					len = 0;
		*/
		//		printf("len->%i\n", len);
				new = ft_strjoin(prev, aux);
				printf("new->%s\n", new);
				free(aux);
				free(prev);
				if (new != 0)
				{	
					free(argv->arg);
					argv->arg = ft_strdup(new);
					free(new);
				}
				printf("char[%i]->%c\n", i, argv->arg[i]);
				i = i + len - 1;
				printf("char[%i]->%c\n", i, argv->arg[i]);
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
