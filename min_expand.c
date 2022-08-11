/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:13:41 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/11 12:41:12 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	expand_aux(char *str, int i, char *aux, t_argv *argv)
{
	char	*prev;
	char	*new;

	prev = ft_substr(str, 0, i);
	new = ft_strjoin(prev, aux);
	free(aux);
	free(prev);
	if (new != 0)
	{	
		free(argv->arg);
		argv->arg = ft_strdup(new);
		free(new);
	}
}

void	expand(t_data *data)
{
	t_argv	*argv;
	int		i[2];
	char	*aux;
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
				expand_aux(argv->arg, i[0], aux, argv);
				i[0] = i[0] + i[1] - 1;
			}	
			i[0]++;
		}
		argv = argv->next;
	}
}

static void	aux_home(t_argv *arg, t_myenv *env)
{
	int	i;

	i = 0;
	while (arg->split[i])
	{
		if (ft_strcmp(arg->split[i], "~") == 0)
		{
			free(arg->split[i]);
			if (env != 0)
				arg->split[i] = ft_strdup(env->value);
			else
				arg->split[i] = 0;
		}
		i++;
	}
}

void	min_home(t_data *data)
{
	t_argv	*arg;
	t_myenv	*env;

	arg = *data->argv;
	env = *data->myenv;
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
			break ;
		env = env->next;
	}
	while (arg)
	{
		aux_home(arg, env);
		arg = arg->next;
	}
}
