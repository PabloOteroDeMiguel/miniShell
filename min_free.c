/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:51:07 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/07 16:40:09 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg_str(char *str, t_argv *argv)
{
	t_argv	*aux;
	int		i;

	aux = argv;
	while (argv)
	{
		i = 0;
		while(argv->split[i])
		{
			free(argv->split[i]);
			i++;
		}
		free(argv->split);
		free(argv->arg);
	//	free(argv->direction);
		aux = argv->next;
		free(argv);
		argv = aux;
	}
	free(argv);
	free(str);
}

void	free_env(t_myenv *myenv)
{
	t_myenv	*aux;

	aux = myenv;
	while (myenv)
	{
		aux = myenv->next;
		free(myenv->key);
		free(myenv->value);
		free(myenv);
		myenv = aux;
	}
	free(myenv);
}

void	free_env_char(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}	
