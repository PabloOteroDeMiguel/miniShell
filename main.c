/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/29 16:44:00 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	min_stop(char *str)
{
	if (ft_strlen(str) != 4)
		return (1);
	else
	{
		if (str[0] != 'e')
			return (1);
		else if (str[1] != 'x')
			return (1);
		else if (str[2] != 'i')
			return (1);
		else if (str[3] != 't')
			return (1);
	}
	return (0);
}

int	main(void)
{
	char	*str;
	t_argv	**argv;
//	t_argv	*aux;
	int		stop;
	int		w;

	atexit(leaks);
	stop = 1;
	argv = malloc(sizeof(t_argv *));
	while (stop != 0)
	{
		w = 0;
		argv = NULL;
		str = readline("\033[;33mMinishell$\033[0m ");
		if (min_stop(str) == 0)
			stop = 0;
	//	read_str(&argv, str);
	//	argv.words = words(str);
	//	printf("-> %d words\n", argv.words);
	//	argv.arg = ft_calloc(argv.words, 1);
		arguments(argv, str);
		//while (argv.arg[w] != '\0')
	//	printf("-> %d argv\n", argv.words);
/*		while (w < argv.words)
		{
			free(argv.arg[w]);
			w++;
		}
		w = 0;
		free_arg_str(str, &argv);*/
	//	aux = argv;
	//	printf("arg[-1]->%s\n", argv->arg);
		print_list(argv);
/*		w = 0;
		while (aux)
		{
			printf("arg[%d]->%s\n", w, aux->arg);
			w++;
			aux = aux->next;
		}*/
		free_arg_str(str, *argv);
	}
	return (0);
}


void	print_list(t_argv **argv)
{
	t_argv	*aux;
	int		w;

	w = 0;
	aux = *argv;
	while (aux)
	{
		printf("arg[%d]->%p->%s\n", w, aux->arg, aux->arg);
		w++;
		aux = aux->next;
	}
}

