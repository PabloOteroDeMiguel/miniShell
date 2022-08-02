/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:15:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/02 11:43:06 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_aux(t_argv *argv, t_myenv *myenv)
{
	if (argv->split[1] == 0)
	{
		if (ft_strcmp(myenv->key, "HOME") == 0)
			chdir(myenv->value);
		else
			printf("Minishell: cd: HOME not set\n");
	}
	else if (argv->split[1] != 0)
	{
		if (chdir(argv->split[1]) == -1)
			printf("Minishell: cd: %s:No such file or directory\n",
				argv->split[1]);
	}
}

void	min_cd(t_data *data)
{
	t_argv	*argv;
	t_myenv	*myenv;

	myenv = *data->myenv;
	while (myenv->next)
	{
		if (ft_strcmp(myenv->key, "HOME") == 0)
			break ;
		myenv = myenv->next;
	}
	argv = *data->argv;
	cd_aux(argv, myenv);
	change_pwd(data->myenv);
}

void	change_pwd(t_myenv **myenv)
{
	char	*buff;
	t_myenv	*aux;

	aux = *myenv;
	while (ft_strcmp(aux->key, "PWD") != 0)
		aux = aux->next;
	buff = getcwd(NULL, 200);
	free(aux->value);
	aux->value = buff;
}
