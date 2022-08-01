/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:37:47 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/01 14:11:28 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(t_argv *arg)
{
	int	r;

	r = 0;
	if ((ft_strcmp(arg->split[0], "echo") == 0)
		|| (ft_strcmp(arg->split[0], "ECHO") == 0)
		|| (ft_strcmp(arg->split[0], "pwd") == 0)
		|| (ft_strcmp(arg->split[0], "PWD") == 0)
		|| (ft_strcmp(arg->arg, "env") == 0)
		|| (ft_strcmp(arg->arg, "ENV") == 0)
		|| (ft_strcmp(arg->split[0], "cd") == 0)
		|| (ft_strcmp(arg->split[0], "export") == 0)
		|| (ft_strcmp(arg->split[0], "unset") == 0)
		|| (ft_strcmp(arg->split[0], "exit") == 0))
			r = 1;
	return (r);
}

int	command_found(t_data *data)
{
	t_argv	*arg;

	arg = *data->argv;
	while (arg)
	{
		if (arg->split[0] != 0)
		{
			if (is_builtin(arg) == 1)
				arg->error_code = 0;
			if (arg->error_code == 127)
			{
				not_cmmd(arg->split[0]);
				data->error_no = 127;
				update_error(data);
			}
			else
				data->error_no = 0;
		}
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
