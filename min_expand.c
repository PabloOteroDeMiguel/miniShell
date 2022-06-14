/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:13:41 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/09 17:50:10 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_str(char *str, t_myenv **myenv, int *len)
{
	t_myenv	*env;
	char	*key;
	char	*extra;
	char	*aux;
	char	*print;
	int		i;

	env = *myenv;
	extra = 0;
	key = ft_strchr(str, '$') + 1;
	i = 0;
	while (key[i])
	{
		if (key[i] == 39 || key[i] == 34 || key[i] == '$' || key[i] == ' ')
		{
		//	aux = ft_strchr(key, key[i]);
			extra = ft_strchr(key, key[i]);
		//	extra = ft_strdup(aux);
			key[i] = 0;
			break ;
		}
		i++;
	}
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			aux = ft_strdup(env->value);
			*len = ft_strlen(aux);
			if (extra != 0)
			{
				print = ft_strjoin(aux, extra);
			//	free(extra);
			}
			else
				print = ft_strdup(aux);
			free(aux);
		//	free(extra);
			return (print);
		}
		env = env->next;
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

int	change(int i, char c)
{
	int	ret;

	ret = 0;
	if ((i == 0) && (c == 34))
		ret = 2;
	else if ((i == 0) && (c == 39))
		ret = 1;
	else if ((i == 1) && (c == 34))
		ret = 1;
	else if ((i == 1) && (c == 39))
		ret = 0;
	else if ((i == 2) && (c == 34))
		ret = 0;
	else if ((i == 2) && (c == 39))
		ret = 2;
	return (ret);
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

	argv = *data->argv;
	while (argv)
	{
		single_quote = 0;
		i = 0;
		len = 0;
		while (argv->arg[i])
		{		
			if ((argv->arg[i] == 39) || (argv->arg[i] == 34))
				single_quote = change(single_quote, argv->arg[i]);
			if (argv->arg[i] == '$' && single_quote != 1)
			{
				prev = ft_substr(argv->arg, 0, i);
				aux = change_str(&argv->arg[i], data->myenv, &len);
				new = ft_strjoin(prev, aux);
				free(aux);
				free(prev);
				if (new != 0)
				{	
					free(argv->arg);
					argv->arg = ft_strdup(new);
					free(new);
				}
				i = i + len - 1;
			}	
			i++;
		}
		argv = argv->next;
	}
}
