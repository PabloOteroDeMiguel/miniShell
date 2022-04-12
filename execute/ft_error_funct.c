/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_funct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:54:00 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/12 12:17:13 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_file_error(char *str)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, ": ", 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	exit(1);
}

void	ft_comm_error(char *str)
{
	char	**s;

	s = ft_split(str, ' ');
	ft_putstr_fd("command not found", 2);
	write(2, ": ", 2);
	ft_putstr_fd(s[0], 2);
	write(2, "\n", 1);
	free_variables_list(s);
	exit(127);
}

void	ft_error(t_comm_path **var, int e)
{
	t_comm_path	*act;

	act = (*var);
	if (act->ok == 0 && e == 0)
	{
		ft_comm_error(act->comm[0]);
	}
}

void	ft_command_validation(t_comm_path **comm_dir, int ferror)
{
	t_comm_path	*var;

	var = (*comm_dir);
	if (var->comm == NULL)
		exit(127);
	ft_error(comm_dir, ferror);
}
