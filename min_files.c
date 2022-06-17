/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:05:04 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/06/17 17:30:11 by potero-d         ###   ########.fr       */
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

static void	set_infile(t_data *data, t_argv *argv, int i)
{
	if (argv->split[i][0] == '<')
	{
		printf("OUTFILE: ");
		if (argv->split[i][1])
		{
			data->infile = ft_strchar(argv->split[i], '<');
			printf("%p\n", argv->split[0]);
			while (i < argv->num_split - 1)
			{
				// free(argv->split[i]);
				argv->split[i] = ft_strdup(argv->split[i + 1]);
				i++;
			}
			free(argv->split[argv->num_split - 1]);
			argv->split[argv->num_split - 1] = 0;
		}
		else
			data->infile = argv->split[i + 1];
		printf(" %s\n", data->infile);
	}
}

static void	set_outfile(t_data *data, t_argv *argv, int i)
{
	if (argv->split[i][0] == '>')
	{
		printf("OUTFILE: ");
		if (argv->split[i][1])
			data->outfile = ft_strchar(argv->split[i], '>');
		else
			data->outfile = argv->split[i + 1];
		printf(" %s\n", data->outfile);
	}
}

void	set_initial_files(t_data *data)
{
	data->infile = "/dev/fd/0";
	data->outfile = "/dev/fd/1";
}

void	check_files(t_data *data)
{
	t_argv	*argv;
	int		i;

	printf("---------------------------\n");
	printf("INFILE: %s\n", data->infile);
	printf("OUTFILE: %s\n", data->outfile);
	printf("---------------------------\n");
	argv = *data->argv;
	while (argv)
	{
		i = -1;
		while (argv->split[++i])
		{
			set_infile(data, argv, i);
			set_outfile(data, argv, i);
		}
		argv = argv->next;
	}
}
