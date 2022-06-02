/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:10:35 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/02 18:49:16 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	read_str(t_argv *argv, char *str)
{
	int	i;

	i = 0;
	argv->s_quote = 0;
	argv->d_quote = 0;
	argv->pipe = 0;
	while (str[i])
	{
		if (str[i] == 34)
			argv->d_quote += 1;
		 else if (str[i] == 39)
			argv->s_quote += 1;
		 else if (str[i] == '|')
			 argv->pipe += 1;
		 i++;
	}
	printf("Inpout:\n"),
	printf("-> %d single quote\n", argv->s_quote);
	printf("-> %d double quote\n", argv->d_quote);
	printf("-> %d pipe\n", argv->pipe);
}*/
/*
int	words(char *str)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (str[i] == ' ')
		i++;
	if (str[i])
		w++;
	while (str[i + 1])
	{
		if (str[i] == ' ' && str[i + 1] != ' ')
			w++;
		i++;
	}
	return (w);
}
*/
void	arguments(t_argv **argv, char *str)
{
	int		i;
	int		len;
	int		w;

	i = 0;
	w = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		len = 0;
/*
		if (str[i] == 39)
		{
			len++;
			while (str[i + len] != 39 && str[i + len])
				len++;
			lst_add_back(argv, lstnew(ft_substr(str, i + 1, len - 1), 1));
			i = i + len ;
			w++;
			len = 0;		}
		else if (str[i] == 34)
		{
			len++;
			while (str[i + len] != 34 && str[i + len])
				len++;
			lst_add_back(argv, lstnew(ft_substr(str, i + 1, len - 1), 2));
			i = i + len ;
			w++;
			len = 0;
		}
*/
		if (str[i] == 124)
		{
			len++;
			while (str[i + len] != 124 && str[i + len])
				len++;
			lst_add_back(argv, lstnew(ft_substr(str, i + 1, len - 1), 3));
			i = i + len ;
			w++;
			len = 0;
		}
		else
		{
		//	while (str[i + len] != 34 && str[i + len] != 39
		//		&& str[i + len] != 124 && str[i + len])
			while (str[i + len] != 124 && str[i + len])
				len++;
			lst_add_back(argv, lstnew(ft_substr(str, i, len), 0));
			i = i + len - 1;
			w++;
			len = 0;
		}
		i++;
	}
}
/*
void	remove_quotes(t_data *data)
{
	int		i;
	int		len;
	char	str;
	char	aux;
	t_argv	*arg_aux;

	arg_aux = *data->argv;
	while (arg)
	{
		i = 0;
		len = 0;
		while (arg_aux->arg[i])
		{
			if (arg_aux->arg[i] == 39)
			{
				if (i != 0)
					aux = ft_substr(arg_aux->arg, 0, i)
}
*/
void	min_split(t_argv **argv)
{
	t_argv	*aux;

	aux = *argv;
	while (aux)
	{
		if (aux->quote == 0)
			aux->split = ft_split(aux->arg, ' ');
		else
		{
			aux->split = malloc(sizeof(char *) * 2);
			aux->split[0] = ft_strdup(aux->arg);
			aux->split[1] = NULL;
		}
		aux = aux->next;
	}
}
