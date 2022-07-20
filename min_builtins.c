/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:11:39 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/20 13:34:18 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	min_builtins(t_data *data)
{
	t_argv  *arg;
	int		r;

	r = 0;
	arg = *data->argv;
	if (arg->split[0] == 0)
		return (0);
	if ((ft_strcmp(arg->split[0], "echo") == 0)
		|| (ft_strcmp(arg->split[0], "ECHO") == 0))
			min_echo(data->argv);
	else if (ft_strcmp(arg->split[0], "pwd") == 0
		|| ft_strcmp(arg->split[0], "PWD") == 0)
			min_pwd(data->myenv);
	else if (ft_strcmp(arg->arg, "env") == 0 || ft_strcmp(arg->arg, "ENV") == 0)
		print_env(data->myenv);
 	else if (ft_strcmp(arg->split[0], "cd") == 0)
		min_cd(data);
	else if (ft_strcmp(arg->split[0], "export") == 0)
	{
		printf("i´m here\n");
		min_export(data);
	}
	else if (ft_strcmp(arg->split[0], "unset") == 0)
		min_unset(data);
	else
		r = 1;
	return (r);
}
