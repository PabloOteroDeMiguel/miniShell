/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:05:04 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/07/21 14:49:40 by potero-d         ###   ########.fr       */
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

static void	set_infile(t_argv *argv, int i)
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

static int	check_if_infile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '<')
		return (1);
	return (0);
}

static void	set_outfile(t_argv *argv, int i)
{
	if (argv->split[i][0] == '>' && argv->split[i][1] != '>')
	{
		free(argv->outfile);
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
	else
	{
		argv->out = 2;
		if (argv->split[i][2])
		{
			argv->outfile = ft_strdup(ft_strchar(argv->split[i], '>') + 1 );
			clean_split(argv, i, 1);
		}
		else
		{
			argv->outfile = ft_strdup(argv->split[i + 1]);
			clean_split(argv, i, 2);
		}
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
		//arg->infile = ft_strdup("/dev/fd/0");
		arg->infile = 0;
		//arg->outfile = ft_strdup("/dev/fd/1");
		arg->outfile = 0;
		arg = arg->next;
	}
}

void	check_files(t_data *data)
{
	t_argv	*argv;
	int		i;
	int		fd;

	argv = *data->argv;
	while (argv)
	{
		i = -1;
		while ((argv->split[++i]) && (i < argv->num_split))
		{
			if (check_if_infile(argv, i) == 1)
			{
				set_infile(argv, i);
				i--;
			}
			else if (check_if_outfile(argv, i) == 1)
			{
				set_outfile(argv, i);
				i--;
				fd = open(argv->outfile, O_CREAT | O_WRONLY , 0644);
				if (fd < 0)
					return ;
				close(fd);
			}
		}
		argv = argv->next;
	}
}
