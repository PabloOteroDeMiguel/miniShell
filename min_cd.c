/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:15:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/04/08 12:02:19 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_cd(t_data *data)
{
	t_argv	*argv;
	t_myenv	*myenv;

	myenv = *data->myenv;
	while (ft_strcmp(myenv->key, "HOME") != 0)
		myenv = myenv->next;
	argv = *data->argv;
	if (argv->split[1] == 0 && argv->next == 0)
		chdir(myenv->value);
	else if (argv->split[1] != 0)
		chdir(argv->split[1]);
	else if (argv->split[1] == 0 && argv->next != 0)
	{
		argv = argv->next;
		chdir(argv->split[0]);
	}
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
