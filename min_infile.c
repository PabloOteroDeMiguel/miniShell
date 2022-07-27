/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_infile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:30:41 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/27 13:06:17 by pmoreno-         ###   ########.fr       */
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

static void	no_here_doc(t_argv *argv, int i)
{
	if (argv->split[i][1])
	{
		argv->infile = ft_strdup(ft_strchar(argv->split[i], '<'));
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
	if (argv->split[i][0] == '<' && argv->split[i][1] != '<' && (argv->split[i][1] || argv->split[i + 1]))
	{
		free(argv->infile);
		no_here_doc(argv, i);
	}
	else if (argv->split[i][0] == '<' && argv->split[i][1] == '<' && (argv->split[i][2] || argv->split[i + 1]))
	{
		free(argv->infile);
		argv->infile = ft_strdup(".here_doc");
		here_doc(argv, i);
		min_here_doc(argv);
		free(argv->eof);
	}
	else
	{
		printf("Minishell: syntax error near unexpected token `newline'");
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
