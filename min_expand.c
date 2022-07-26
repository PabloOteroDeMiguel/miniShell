/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:13:41 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/12 17:24:21 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
			extra = ft_strdup(ft_strchr(key, key[i]));
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
	if (extra == 0)
	{
		print = malloc(sizeof(char *) * 1);
		print[0] = 0;
	}
	else
		print = ft_strdup(extra);
	return (print);
}
*/
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
	{
		if (extra == 0)
		{
			print = malloc(sizeof(char *) * 1);
			print[0] = 0;
		}
		else
			print = ft_strdup(extra);
	}
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

static void	expand_aux(char *str, int i, char **new, char *aux)
{
	char	*prev;

	prev = ft_substr(str, 0, i);
	*new = ft_strjoin(prev, aux);
	free(aux);
	free(prev);
}

void	expand(t_data *data)
{
	t_argv	*argv;
	int		i[2];
	char	*aux;
	char	*new;
	int		single_quote;

	argv = *data->argv;
	while (argv)
	{
		single_quote = 0;
		i[0] = 0;
		i[1] = 0;
		while (argv->arg[i[0]])
		{		
			if ((argv->arg[i[0]] == 39) || (argv->arg[i[0]] == 34))
				single_quote = change(single_quote, argv->arg[i[0]]);
			if (argv->arg[i[0]] == '$' && single_quote != 1)
			{
				aux = change_str(&argv->arg[i[0]], data->myenv, &i[1]);
				expand_aux(argv->arg, i[0], &new, aux);
				if (new != 0)
				{	
					free(argv->arg);
					argv->arg = ft_strdup(new);
					free(new);
				}
				i[0] = i[0] + i[1] - 1;
			}	
			i[0]++;
		}
		argv = argv->next;
	}
}
