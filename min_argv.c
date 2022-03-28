/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:10:35 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/28 13:11:32 by potero-d         ###   ########.fr       */
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
	int p;

	i = 0;
	w = 0;
//	len = 0;
//	while (str[i] == ' ')
//		i++;
	while (str[i])
	{
		printf("str[%d]->%c\n", i, str[i]);
		len = 0;
		if (str[i] == 39)
		{
			printf("i->%d\n", i);
			len++;
			while (str[i + len] != 39 && str[i + len])
				len++;
			printf("len->%d\n", len);
			argv->arg[w] = ft_substr(str, i + 1, len - 1);
			i = i + len ;
			printf("i+len->%d\n", i);
			w++;
			len = 0;
		}
		else if (str[i] == 34)
		{
			len++;
			while (str[i + len] != 34 && str[i + len])
				len++;
			argv->arg[w] = ft_substr(str, i + 1, len - 1);
			i = i + len ;
			w++;
			len = 0;
		}
		else if (str[i] == '|')
		{
			len++;
			while (str[i + len] != '|' && str[i + len])
				len++;
			argv->arg[w] = ft_substr(str, i + 1, len - 1);
			i = i + len ;
			w++;
			len = 0;
		}
		//else if (str[i] != 34 && str[i] != 39 && str[i] != '|' && str[i])
		else
		{
			while (str[i + len] != 34 && str[i + len] != 39 && str[i + len] != '|' && str[i + len])
				len++;
			argv->arg[w] = ft_substr(str, i, len);
			i = i + len - 1;
			w++;
			len = 0;
		}
		i++;
	}
	p = 0;
	argv->words = w;
	while (p < w)
	{
		printf("%d\n", p);
		printf("arg[%d]->%s\n", p, argv->arg[p]);
		printf("%d\n", p);
		p++;
	}
}


