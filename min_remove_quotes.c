/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_remove_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:01:20 by potero            #+#    #+#             */
/*   Updated: 2022/06/06 17:21:28 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static int  change_quote(int q, char c)
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
*/

char	*quotes(char *str)
{
	char	*ret;
	char	*aux;
	char	*aux2;
	char	c;
	int		i;
	int		j;

	//Esto parece una fumada pero funciona
	//Elimina las comillas que sobran pero deja las que están dentro de otras
	// Por ejemplo "'HOLA'" tiene que qedar como 'HOLA'
	i = 0;
	while (str[i])
	{
		if ((str[i] == 34) || (str[i] == 39))
		{
			c = str[i];
		//	printf("str[%i]->%c\n", i, c);
			aux = ft_substr(str, 0, i);
		//	printf("aux->%s\n", aux);
			j = i + 1;
			while (str[j] && str[j] != c)
			{	
			//	printf("str[%i]->%c\n", j, str[j]);
				j++;
			}
			aux2 = ft_substr(str, i + 1, j - i - 1);
		//	printf("aux2->%s\n", aux2);
			ret = ft_strjoin(aux, aux2);
			free(aux);
			free(aux2);
			aux = ft_substr(str, j + 1 , ft_strlen(str) - j);
			aux2 = ft_strjoin(ret, aux);
			free(str);
			str = ft_strdup(aux2);
		//	printf("STR->%s\n", str);
		//	printf("i->%i\n", i);
		//	printf("j->%i\n", j);
			i = j - 2; //-2 por las dos comillas que hemos quitado
		}
	//	printf("I->%i\n", i + 1);
		i++;
	}
	return (aux2);
}

void	remove_quotes(t_argv **argv)
{
	int		i;
	char	*str;
	t_argv	*aux;

	aux = *argv;
	while (aux)
	{
		i = 0;
		if (ft_strchr(aux->arg, 34) != 0 || ft_strchr(aux->arg, 39 != 0))
		{
			str = quotes(aux->arg);
			//printf("str->%s\n", str);
			free(aux->arg);
			aux->arg = ft_strdup(str);
			free(str);
		}
		while (aux->split[i])
		{
			if (ft_strchr(aux->split[i], 34) != 0 || ft_strchr(aux->split[i], 39 != 0))
			{
				str = quotes(aux->split[i]);
				free(aux->split[i]);
				aux->split[i] = ft_strdup(str);
				free(str);
			}
			i++;
		}
		aux = aux->next;
	}		
}
