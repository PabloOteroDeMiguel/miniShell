/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:11:39 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/01 13:06:12 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	min_builtins(t_argv *arg, t_data *data)
{
	int		r;

	r = 0;
	if (arg->split[0] == 0)
		return (0);
	if ((ft_strcmp(arg->split[0], "echo") == 0)
		|| (ft_strcmp(arg->split[0], "ECHO") == 0))
		min_echo(&arg);
	else if (ft_strcmp(arg->split[0], "pwd") == 0
		|| ft_strcmp(arg->split[0], "PWD") == 0)
		min_pwd(data->myenv);
	else if ((ft_strcmp(arg->split[0], "env") == 0
			|| ft_strcmp(arg->split[0], "ENV") == 0) && !arg->split[1])
		print_env(data->myenv);
	else if (ft_strcmp(arg->split[0], "cd") == 0)
		min_cd(data);
	else if (ft_strcmp(arg->split[0], "export") == 0)
		min_export(data);
	else if (ft_strcmp(arg->split[0], "unset") == 0)
		min_unset(data);
	else
		r = 1;
	return (r);
}
