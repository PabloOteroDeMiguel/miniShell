/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:10:35 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/09 13:15:57 by potero           ###   ########.fr       */
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
/*
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
*/

static int	change_quote(int q, char c)
{
	int r;
	
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
	int q;

	q = 0;
	i = 0;
	while (s[i] == ' ')
		i++;
	w = 1;
	while (s[i + 1])
	{
		if (s[i] == ' ' && s[i + 1] != ' ' && q == 0)
			w++;
		else if (s[i] == 39) //single quote. Esto se puede poner en un solo else if (195 y 197)
			q = change_quote(q, s[i]);
		else if (s[i] == 34) //double quote
			q = change_quote(q, s[i]);
		i++;
	}
	return (w);	
}

void static aux(char ***str, char *s)
{
	int	i;
	int	j;
	int w;
	int	q;

	i = 0;
	j = 0;
	w = 0;
	q = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
	//	printf("s[%i]->%c\n", i, s[i]);
	//	printf("q[%i]->%i\n", i, q);
	//	printf("j[%i]->%i\n", i, j);
		if ((s[i] == ' ') && (q == 0))
		{
			(*str)[w] = ft_substr(s, i - j, j);
			while (s[i + 1] == ' ')
				i++;
			w++;
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
	t_argv	*argv;

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
	//	printf("w->%i\n", words);		
		argv->split = malloc(sizeof(char *) * (words + 1));
		if (!argv->split)
			argv->split = 0;
		aux(&argv->split, argv->arg);
		argv = argv->next;
	}
}
