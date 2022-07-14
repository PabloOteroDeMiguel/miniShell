/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:05:04 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/07/14 16:23:32 by potero-d         ###   ########.fr       */
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

static void	clean_split(t_argv *argv, int i, int z)
{
	char	**split_new;
	int		j;

	split_new = malloc(sizeof(char *) * argv->num_split);
	j = 0;

	while ((j < argv->num_split - z) && (argv->split[j + z]))
	{
		if (j < i)
			split_new[j] = ft_strdup(argv->split[j]);
		else if (j >= i)
			split_new[j] = ft_strdup(argv->split[j + z]);
		j++;
	}
	split_new[j] = 0;
	free_env_char(argv->split);
	argv->split = split_new;
	argv->num_split--;
}

static void	set_infile(t_data *data, t_argv *argv, int i)
{
	if (argv->split[i][0] == '<' && argv->split[i][1] != '<')
	{
		free(argv->infile);
		printf("INFILE: ");
		if (argv->split[i][1])
		{
			data->infile = ft_strdup(ft_strchar(argv->split[i], '<'));
			argv->infile = ft_strdup(ft_strchar(argv->split[i], '<'));
			clean_split(argv, i, 1);
		}
		else
		{
			data->infile = ft_strdup(argv->split[i + 1]);
			argv->infile = ft_strdup(argv->split[i + 1]);
			clean_split(argv, i, 2);
		}
		printf(" %s\n", argv->infile);
	}
}

static int	check_if_infile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '<')
		return (1);
	return (0);
}

static void	set_outfile(t_data *data, t_argv *argv, int i)
{

	if (argv->split[i][0] == '>' && argv->split[i][1] != '>')
	{
		free(argv->outfile);
		printf("OUTFILE: ");
		if (argv->split[i][1])
		{
			data->outfile = ft_strdup(ft_strchar(argv->split[i], '>'));
			argv->outfile = ft_strdup(ft_strchar(argv->split[i], '>'));
			clean_split(argv, i, 1);

		}
		else
		{
			data->outfile = ft_strdup(argv->split[i + 1]);
			argv->outfile = ft_strdup(argv->split[i + 1]);
			clean_split(argv, i, 2);
		}
		printf(" %s\n", data->outfile);
	}
}

static int	check_if_outfile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '>')
		return (1);
	return (0);
}

void	set_initial_files(t_data *data)
{
	t_argv	*arg;

	arg = *data->argv;
	while (arg)
	{
		arg->infile = ft_strdup("/dev/fd/0");
		arg->outfile = ft_strdup("/dev/fd/1");
		arg = arg->next;
	}
	data->infile = "/dev/fd/0";
	data->outfile = "/dev/fd/1";
}

void	check_files(t_data *data)
{
	t_argv	*argv;
	int		i;
	int		fd;
	
//	argv = *data->argv;
	printf("---------------------------\n");
	printf("INFILE: %s\n", data->infile);
	printf("OUTFILE: %s\n", data->outfile);
	printf("---------------------------\n");
	/*
	i = 0;
	while (argv)
	{
		printf("infile[%i]: %s\n", i, argv->infile);
		printf("outfile[%i]: %s\n", i, argv->outfile);
		i++;
		argv = argv->next;
	}
	*/
	argv = *data->argv;
	while (argv)
	{
		i = -1;
		while ((argv->split[++i]) && (i < argv->num_split))
		{
			if (check_if_infile(argv, i) == 1)
			{
				set_infile(data, argv, i);
				i--;
			}
			else if (check_if_outfile(argv, i) == 1)
			{
				set_outfile(data, argv, i);
				i--;
				fd = open(argv->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
				if (fd < 0)
					return ;
				close(fd);
			}
		}
		argv = argv->next;
	}
}

