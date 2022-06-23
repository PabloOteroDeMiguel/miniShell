/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:10:35 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/23 11:25:42 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arguments(t_argv **argv, char *str)
{
	int		i;
	int		len;

	i = 0;
	while (str[i])
	{
		len = 0;
		if (str[i] == 124)
		{
			len++;
			while (str[i + len] != 124 && str[i + len])
				len++;
			lst_add_back(argv, lstnew(ft_substr(str, i + 1, len - 1)));
			i = i + len ;
		}
		else
		{
			while (str[i + len] != 124 && str[i + len])
				len++;
			lst_add_back(argv, lstnew(ft_substr(str, i, len)));
			i = i + len - 1;
		}
		i++;
	}
}

static int	change_quote(int q, char c)
{
	int	r;

	r = 0;
	if ((c == 39) && (q == 0))
		r = 1;
	else if ((c == 39) && (q == 1))
		r = 0;
	else if ((c == 39) && (q == 2))
		r = 2;
	else if ((c == 34) && (q == 0))
		r = 2;
	else if ((c == 34) && (q == 1))
		r = 1;
	else if ((c == 34) && (q == 2))
		r = 0;
	return (r);
}

static int	min_words(char *s)
{
	int	w;
	int	i;
	int	q;

	q = 0;
	i = 0;
	while (s[i] == ' ')
		i++;
	w = 1;
	while (s[i + 1])
	{
		if (s[i] == ' ' && s[i + 1] != ' ' && q == 0)
			w++;
		else if (s[i] == 39 || s[i] == 34)
			q = change_quote(q, s[i]);
		i++;
	}
	return (w);
}

void static	aux(char ***str, char *s, int q, int w)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if ((s[i] == ' ') && (q == 0))
		{
			(*str)[w++] = ft_substr(s, i - j, j);
			while (s[i + 1] == ' ')
				i++;
			j = 0;
		}
		else if ((s[i] != ' ') || (s[i] == ' ' && q != 0))
			j++;
		if (s[i] == 34 || s[i] == 39)
			q = change_quote(q, s[i]);
		i++;
	}
	if (s[i - 1] != ' ')
		(*str)[w++] = ft_substr(s, i - j, j);
	(*str)[w] = 0;
}

void	min_split(t_data *data)
{
	int		words;
	int		w;
	int		q;
	t_argv	*argv;

	w = 0;
	q = 0;
	argv = *data->argv;
	while (argv)
	{
		if (!argv->arg)
			argv->split = 0;
		if (ft_strlen(argv->arg) == 0)
		{
			argv->split = malloc(sizeof(char *) * 1);
			argv->split[0] = 0;
		}
		words = min_words(argv->arg);
		argv->num_split = words;
		argv->split = malloc(sizeof(char *) * (words + 1));
		if (!argv->split)
			argv->split = 0;
		aux(&argv->split, argv->arg, q, w);
		argv = argv->next;
	}
}
