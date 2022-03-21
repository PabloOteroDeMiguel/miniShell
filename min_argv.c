/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:10:35 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/21 13:55:02 by potero-d         ###   ########.fr       */
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

int	words(char *str)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (str[i] == ' ')
		i++;
	if (str[i])
		w++;
	while (str[i + 1])
	{
		if (str[i] == ' ' && str[i + 1] != ' ')
			w++;
		i++;
	}
	return (w);
}

void	arguments(t_argv *argv, char *str)
{
	int	i;
	int len;
	int	w;

	i = 0;
	w = 0;
//	len = 0;
//	while (str[i] == ' ')
//		i++;
	while (str[i])
	{
		len = 0;
		if (str[i] == 39)
		{
			len++;
			while (str[len] != 39 && str[len])
				len++;
			argv->arg[w] = ft_substr(str, i + 1, len - 1);
			i = i + len ;
			w++;
			len = 0;
		}
		else if (str[i] == 34)
		{
			len++;
			printf("len->%d\n", len);
			while (str[len] != 34 && str[len])
			{
				len++;
			}
			printf("len->%d\n", len);
			argv->arg[w] = ft_substr(str, i + 1, len - 1);
			i = i + len ;
			w++;
			len = 0;
		}
		else if (str[i] == '|')
		{
			len++;
			while (str[len] != '|' && str[len])
				len++;
			argv->arg[w] = ft_substr(str, i + 1, len - 1);
			i = i + len ;
			w++;
			len = 0;
		}
		else if (str[i] != 34 && str[i] != 39 && str[i] != '|' && str[i])
		{
			while (str[len] != 34 && str[i] != 39 && str[i] != '|' && str[len])
				len++;
			argv->arg[w] = ft_substr(str, i, len);
			i = i + len;
			w++;
			len = 0;
		}
		i++;
	}
	w = 0;
	while (argv->arg[w] != 0)
	{
		printf("arg[%d]->%s\n", w, argv->arg[w]);
		w++;
	}
}


