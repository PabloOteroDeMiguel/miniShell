/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:05:04 by pmoreno-          #+#    #+#             */
/*   Updated: 2022/07/27 12:57:48 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_split(t_argv *argv, int i, int z)
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

void	set_initial_files(t_data *data)
{
	t_argv	*arg;

	arg = *data->argv;
	while (arg)
	{
		arg->infile = 0;
		arg->outfile = 0;
		arg = arg->next;
	}
}

static void	check_aux(t_argv *argv)
{
	int	i;
	int	fd;

	i = -1;
	while ((argv->split[++i]) && (i < argv->num_split))
	{
		if (check_if_infile(argv, i) == 1)
		{
			if (set_infile(argv, i))
				break ;
			i--;
		}
		else if (check_if_outfile(argv, i) == 1)
		{
			set_outfile(argv, i);
			i--;
			fd = open(argv->outfile, O_CREAT | O_WRONLY, 0644);
			if (fd < 0)
				return ;
			close(fd);
		}
	}
}

void	check_files(t_data *data)
{
	t_argv	*argv;

	argv = *data->argv;
	while (argv)
	{
		check_aux(argv);
		argv = argv->next;
	}
}
