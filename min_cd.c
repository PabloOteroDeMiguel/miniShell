/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:15:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/03 11:47:30 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(char *str, t_data *data)
{
	write(2, "Minishell: cd: ", 15);
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	data->error_no = 1;
}

static void	cd_aux(t_argv *argv, t_myenv *myenv, t_data *data)
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
			cd_error(argv->split[1], data);
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
	cd_aux(argv, myenv, data);
	change_pwd(data->myenv);
}

static void	pwd_error(char *str)
{
	write(2, "cd: error retrieving current directory: ", 40);
	ft_putstr_fd(str, 2);
	write(2, ": cannot access parent directories: ", 36);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
}

void	change_pwd(t_myenv **myenv)
{
	char	*buff;
	t_myenv	*aux;

	aux = *myenv;
	while (ft_strcmp(aux->key, "PWD") != 0)
		aux = aux->next;
	buff = getcwd(NULL, 200);
	if (buff == 0)
		pwd_error("getcwd");
	else
	{
		free(aux->value);
		aux->value = buff;
	}
}
