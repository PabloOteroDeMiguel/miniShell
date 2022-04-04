/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:15:16 by potero-d          #+#    #+#             */
/*   Updated: 2022/04/04 10:45:04 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	min_cd(t_data *data)
{
	char	*buff;
	t_argv	*argv;

	argv = *data->argv;
	printf("%s\n", argv->split[0]);
	buff = getcwd(NULL, 200);
	printf("%s\n", buff);
}
