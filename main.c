/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/11 13:40:41 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	min_stop(char *str)
{
	if (ft_strlen(str) != 4)
		return (1);
	else
	{
		if (str[0] != 'e')
			return (1);
		else if (str[1] != 'x')
			return (1);
		else if (str[2] != 'i')
			return (1);
		else if (str[3] != 't')
			return (1);
	}
	return (0);
}

int	main(void)
{
	char	*str;
	char	**argv;
	int		i;
	int		stop;

	atexit(leaks);
	stop = 1;
	while (stop != 0)
	{
		str = readline("\033[;33mMinishell$\033[0m ");
		if (min_stop(str) == 0)
			stop = 0;
		argv = ft_split(str, ' ');
		i = 0;
		while (argv[i])
		{
			printf("%s\n", argv[i]);
			free(argv[i]);
			i++;
		}
		free(argv);
		free(str);
	}
	return (0);
}
