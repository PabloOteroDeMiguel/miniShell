/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_outfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:44:25 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/27 13:35:37 by pmoreno-         ###   ########.fr       */
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

static void	no_appen(t_argv *argv, int i)
{
	if (argv->split[i][1])
	{
		argv->outfile = ft_strdup(ft_strchar(argv->split[i], '>'));
		clean_split(argv, i, 1);
	}
	else
	{
		argv->outfile = ft_strdup(argv->split[i + 1]);
		clean_split(argv, i, 2);
	}
}

static void	appen(t_argv *argv, int i)
{
	if (argv->split[i][2])
	{
		argv->outfile = ft_strdup(ft_strchar(argv->split[i], '>') + 1);
		clean_split(argv, i, 1);
	}
	else
	{
		argv->outfile = ft_strdup(argv->split[i + 1]);
		clean_split(argv, i, 2);
	}
}

int	set_outfile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '>' && argv->split[i][1] != '>'
			&& (argv->split[i][1] || argv->split[i + 1]))
	{
		free(argv->outfile);
		no_appen(argv, i);
	}
	else if (argv->split[i][0] == '>' && argv->split[i][1] == '>'
			&& (argv->split[i][2] || argv->split[i + 1]))
	{
		argv->out = 2;
		free(argv->outfile);
		appen(argv, i);
	}
	else
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		clean_split(argv, i, 1);
		return (1);
	}
	return (0);
}

int	check_if_outfile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '>')
		return (1);
	return (0);
}
