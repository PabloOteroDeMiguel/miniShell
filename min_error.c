/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:37:47 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/29 11:20:41 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_found(t_data *data)
{
	t_argv	*arg;

	arg = *data->argv;
	while (arg)
	{
		if (arg->error_code == 127)
		{
			not_cmmd(arg->split[0]);
			data->error_no = 127;
			update_error(data);
		}
		else
			data->error_no = 0;
		arg = arg->next;
	}
	update_error(data);
	return (0);
}

void	update_error(t_data *data)
{
	char	*aux;
	t_myenv	*env;

	env = *data->myenv;
	while (env)
	{
		if (ft_strcmp(env->key, "?") == 0)
		{
			free(env->value);
			aux = ft_itoa(data->error_no);
			env->value = ft_strdup(aux);
			free(aux);
		}
		env = env->next;
	}
}

void	pipe_error(t_data *data)
{
	t_argv	*arg;

	arg = *data->argv;
/*	if (data->error_no == 1)
	{
		printf("Minishell: %s: No such file or directory\n", data->infile);
		printf("Minishell: %s: Permission denied\n", data->infile);
	}*/
	if (data->error_no == 127)
		printf("Minishell. %s: No such file or directory\n", arg->split[0]);
	update_error(data);
}

void	fd_error(char *str)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, ": ", 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	exit (1);
}
