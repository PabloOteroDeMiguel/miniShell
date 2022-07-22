/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_infile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:30:41 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/22 12:44:14 by potero-d         ###   ########.fr       */
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

void	set_infile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '<' && argv->split[i][1] != '<')
	{
		free(argv->infile);
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
	else
	{
		argv->infile = ft_strdup(".here_doc");
		if (argv->split[i][2])
		{
			argv->eof = ft_strdup(ft_strchar(argv->split[i], '<') + 1 );
			clean_split(argv, i, 1);
		}
		else
 		{
			argv->eof = ft_strdup(argv->split[i + 1]);
			clean_split(argv, i, 2);
		}
 		min_here_doc(argv);
		free(argv->eof);
	}
}

int	check_if_infile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '<')
		return (1);
	return (0);
}
