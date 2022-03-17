/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:10:35 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/17 13:43:00 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_str(t_argv *argv, char *str)
{
	int	i;

	i = 0;
	argv->s_quote = 0;
	argv->d_quote = 0;
	argv->pipe = 0;
	while (str[i])
	{
		if (str[i] == 34)
			argv->d_quote += 1;
		 else if (str[i] == 39)
			argv->s_quote += 1;
		 else if (str[i] == '|')
			 argv->pipe += 1;
		 i++;
	}
	printf("Inpout:\n"),
	printf("-> %d single quote\n", argv->s_quote);
	printf("-> %d double quote\n", argv->d_quote);
	printf("-> %d pipe\n", argv->pipe);
}
/*
int	check_pipe(t_argv *argv, char *str, int	pipes)
{
	int	i;
	int	pipe;
	int	quote;

	i = 0;
	pipe = 0
*/
