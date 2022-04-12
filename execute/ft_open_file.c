/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 13:00:08 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/04/12 12:19:30 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_file(char **argv, int argc)
{
	int	fd;

	fd = 0;
	if (argc != 4)
		fd = open(argv[1], O_RDONLY);
	return (fd);
}
