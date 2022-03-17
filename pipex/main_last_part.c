/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_last_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:11:55 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/03/10 12:12:01 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_final_part(t_comm_path **comm_dir, char **l_paths)
{
	ft_check_errors(comm_dir);
	free_variables_list(l_paths);
	free_variables(comm_dir);
	free(comm_dir);
}
