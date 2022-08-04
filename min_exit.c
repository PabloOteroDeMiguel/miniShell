/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:31:15 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/04 12:33:46 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_exit(t_argv *arg, t_data *data)
{
	if (ft_strcmp(arg->split[0], "exit") == 0)
	{
		if (arg->split[1])
		{
			if (ft_atoi(arg->split[1]))
			{
				data->error_no = ft_atoi(arg->split[1]);
				update_error(data);
				exit (ft_atoi(arg->split[1]));
			}
			else
				printf("Minishell: exit: %s: numeric argument required",
					arg->split[1]);
		}
		printf("exit\n");
		exit (0);
	}
}
