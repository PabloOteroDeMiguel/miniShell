/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:37:47 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/20 13:38:14 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_found(t_data *data)
{
	t_argv	*arg;

	arg = *data->argv;
	while (arg)
	{
		if (ft_strcmp(arg->split[0], "export") == 0
			|| ft_strcmp(arg->split[0], "unset") == 0)
				arg->error_code = 0;
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
