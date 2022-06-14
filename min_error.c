/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:37:47 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/14 13:37:48 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	command_found(t_data *data)
{
	t_argv	*arg;
	int		p;

	arg = *data->argv;
	while (arg->next)
		arg = arg->next;
	if (arg->error_code != 127)
		p = 1;
	else
		p = 0;
	/*si el último existe no hay que imprimir cmmd not found */
	arg = *data->argv;
	while (arg)
	{
		if (arg->error_code == 127)
		{
			if (p == 0)
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
	
