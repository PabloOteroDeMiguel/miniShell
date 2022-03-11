/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/11 11:58:54 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

/*
int	main(int argc, char *argv[])
{
	char	**str;
	int 	i;
	
	i = 0;
	if (argc > 1)
	{
		str = ft_split(argv[1], ' ');
		while (str[i])
		{
			printf("%s\n", str[i]);
			i++;
		}
	}
	return (0);
}
*/
int	main(void)
{
	char	*str;
	while (1)
	{
		str = readline("Minishell$ ");
		printf("you type %s\n", str);
		free(str);
	}
	return (0);
}
