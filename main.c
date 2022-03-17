/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/17 13:43:02 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_argv	argv;
	int		stop;

	atexit(leaks);
	stop = 1;
	while (stop != 0)
	{
		str = readline("\033[;33mMinishell$\033[0m ");
		if (min_stop(str) == 0)
			stop = 0;
		read_str(&argv, str);
		if(argv.pipe != 0)
		{
			if (argv.d_quote > 0 || argv.s_qute > 0)
			{
				check_pipe(&argv, str, arg);
			}
		}
		free(str);
	}
	return (0);
}
