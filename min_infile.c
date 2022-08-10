/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_infile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:30:41 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/10 13:44:31 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strchar(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(str))
	{
		if (str[i] == (unsigned char)c)
			return ((char *)(&str[i + 1]));
		i++;
	}
	if (c == '\0')
		return (0);
	return (0);
}

static int	where_is(char c, int pos, char *str)
{
	while (str[pos])
	{
		if (str[pos] == c)
			return (pos);
		pos++;
	}
	return (-1);
}

static char	*no_quotes_file(char *str)
{
	char	*aux;
	int		i;
	int		pos;
	int		j;

	i = 0;
	j = 0;
	aux = 0;
	if (str[i] == 34 || str[i] == 39)
	{
		while (str[i] == 32)
			i++;
		pos = where_is(32, i, str);
		if (pos != -1)
		{
			aux = malloc(pos - i + 1);
			while (i <= pos)
			{
				aux[0] = str[i];
				j++;
				i++;
			}
			aux[j] = '\0';
		}
	}
	return (str);
}

static void	no_here_doc(t_argv *argv, int i)
{
	if (argv->split[i][1])
	{
		argv->infile = ft_strdup(no_quotes_file(ft_strchar(argv->split[i], '<')));
		clean_split(argv, i, 1);
	}
	else
	{
		argv->infile = ft_strdup(argv->split[i + 1]);
		clean_split(argv, i, 2);
	}
}

static void	here_doc(t_argv *argv, int i)
{
	if (argv->split[i][2])
	{
		argv->eof = ft_strdup(ft_strchar(argv->split[i], '<') + 1);
		clean_split(argv, i, 1);
	}
	else
	{
		argv->eof = ft_strdup(argv->split[i + 1]);
		clean_split(argv, i, 2);
	}
}

int	set_infile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '<' && argv->split[i][1] != '<'
			&& (argv->split[i][1] || argv->split[i + 1]))
	{
		free(argv->infile);
		no_here_doc(argv, i);
	}
	else if (argv->split[i][0] == '<' && argv->split[i][1] == '<'
			&& (argv->split[i][2] || argv->split[i + 1]))
	{
		free(argv->infile);
		argv->infile = ft_strdup(".here_doc");
		here_doc(argv, i);
		min_here_doc(argv);
		free(argv->eof);
	}
	else
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		clean_split(argv, i, 1);
		return (1);
	}
	return (0);
}

int	check_if_infile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '<')
		return (1);
	return (0);
}
