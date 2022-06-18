/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:05:04 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/06/17 17:56:08 by pmoreno-         ###   ########.fr       */
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
	if (argv->split[i][0] == '<' && argv->split[i][1] != '<')
	{
		printf("INFILE: ");
		if (argv->split[i][1])
		{
			data->infile = ft_strchar(argv->split[i], '<');
			while (i < argv->num_split - 1)
			{
				if (argv->split[i + 1])
				{
					argv->split[i] = ft_strdup(argv->split[i + 1]);
					argv->split[i + 1] = 0;
					i++;
				}
				else
				{
					argv->split[i] = 0;
					return ;	
				}			
			}
		}
		else
		{
			data->infile = argv->split[i + 1];
			while (i < argv->num_split - 2)
			{
				if (argv->split[i + 2])
				{
					argv->split[i] = 0;
					argv->split[i] = ft_strdup(argv->split[i + 2]);
					i++;
				}
			}
			argv->split[argv->num_split - 2] = 0;
			argv->split[argv->num_split - 1] = 0;
		}
		printf(" %s\n", data->infile);
	}
}

static int	check_if_infile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '<')
		return (1);
	return (0);
}

static int	set_outfile(t_data *data, t_argv *argv, int i)
{
	int	j;

	j = i;
	if (argv->split[i][0] == '>' && argv->split[i][1] != '>')
	{
		printf("OUTFILE: ");
		if (argv->split[i][1])
		{
			data->outfile = ft_strchar(argv->split[i], '>');
			while (i < argv->num_split - 1)
			{
				if (argv->split[i + 1])
				{
					argv->split[i] = ft_strdup(argv->split[i + 1]);
					argv->split[i + 1] = 0;
					i++;
				}
				else
				{
					argv->split[i] = 0;
					return (j);	
				}
			}
		}
		else
		{
			data->outfile = argv->split[i + 1];
			while (i < argv->num_split - 2)
			{
				argv->split[i] = 0;
				argv->split[i] = ft_strdup(argv->split[i + 2]);
				i++;
			}
			argv->split[argv->num_split - 2] = 0;
			argv->split[argv->num_split - 1] = 0;
			return (j);
		}
		write(1, "AAAAAA3\n", 9);
		printf(" %s\n", data->outfile);
	}
	return(j+1);
}

static int	check_if_outfile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '>')
		return (1);
	return (0);
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
	int		fd;

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
			if (check_if_infile(argv, i) == 1)
			{
				printf("Es infile\n");
				set_infile(data, argv, i);
			}
			else if (check_if_outfile(argv, i) == 1)
			{
				printf("Es outfile\n");
				i = set_outfile(data, argv, i);
				fd = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
				if (fd < 0)
					return ;
				close(fd);
			}
		}
		write(1, "ADIO4\n", 6);
		if (argv->next)
			argv = argv->next;
		else
			return ;
	}
}
