/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:10:35 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/14 14:05:32 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	min_quotes(char *str, char **argv)
{
	int	db_q;
	int	sg_q;
	int i;

	i = 0;
	db_q = 0;
	sg_q = 0;	
	while (str[i])
	{
		if (str[i] == 34)
		{
			argv = ft_split(str, 34);
			db_q++;
			break ;
		}
		else if (str[i] == 39)
		{
			sg_q++;
			argv = ft_split(str, 39);
		}
		i++;
	}
//	printf("-> %d single quotes\n", sg_q);
//	printf("-> %d double quotes\n", db_q);
	return (0);
}
