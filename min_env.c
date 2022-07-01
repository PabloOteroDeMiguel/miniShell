/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:42:58 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/01 12:01:13 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_myenv	*envnew(char *str)
{
	t_myenv	*element;
	char	*aux;

	element = malloc(sizeof(t_myenv));
	if (ft_strcmp(str, "?") == 0)
		aux = "0";
	else if (ft_strcmp(str, "PWD") == 0)
		aux = getcwd(NULL, 200);
	else if (ft_strcmp(str, "SHLVL") == 0)
		aux = shlvl(getenv(str));
	//	aux = "1";
	else
		aux = getenv(str);
	if (!element)
		return (NULL);
	element->key = str;
	element->value = ft_strdup(aux);
	element->next = NULL;
	if (ft_strcmp(str, "PWD") == 0)
		free(aux);
	return (element);
}

t_myenv	*envlast(t_myenv *myenv)
{
	t_myenv	*aux;

	aux = myenv;
	if (!myenv)
		return (0);
	while (aux->next != 0)
		aux = aux->next;
	return (aux);
}

void	env_add_back(t_myenv **myenv, t_myenv *new)
{
	t_myenv	*aux;

	if (*myenv)
	{
		aux = envlast(*myenv);
		aux->next = new;
	}
	else
		*myenv = new;
}

void	min_getenv(char **envp, t_myenv **myenv)
{
	int		i;
	int		j;
	char	*error;

	i = 0;
	if (!envp[i])
	{
		envp[0] = "PWD=";
		envp[1] = "SHLVL=";
		envp[2] = 0;
	}
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		env_add_back(myenv, envnew(ft_substr(envp[i], 0, j)));
		i++;
	}
	error = malloc(sizeof(char *) * 2);
	error[0] = 63;
	error[1] = 0;
	env_add_back(myenv, envnew(error));
}

char	**env_to_char(t_myenv **myenv)
{
	char	**str;
	char	*auxstr;
	t_myenv	*aux;
	int		i;

	i = 0;
	aux = *myenv;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	aux = *myenv;
	str = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (aux)
	{
		auxstr = ft_strjoin(aux->key, "=");
		str[i] = ft_strjoin(auxstr, aux->value);
		free(auxstr);
		i++;
		aux = aux->next;
	}
	str[i] = 0;
	return (str);
}
