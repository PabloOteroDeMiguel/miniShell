/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:51:07 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/29 17:45:53 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg_str(char *str, t_argv *argv)
{
	t_argv	*aux;

	aux = argv;
	while (argv)
	{
		free(argv->arg);
		aux = argv->next;
		free(argv);
		argv = aux;
	}
	free(argv);
	free(str);
}
