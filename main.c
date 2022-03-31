/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/03/31 12:24:29 by potero-d         ###   ########.fr       */
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

void	min_builtins(char *str, t_argv **argv)
{
	t_argv *aux;

	aux = *argv;
	if ((ft_strncmp(str, "echo", 4) == 0) || (ft_strncmp(str, "ECHO", 4) == 0))
		min_echo(argv);
	else if (ft_strcmp(aux->split[0], "pwd") == 0 || ft_strcmp(aux->split[0], "PWD") == 0)
		printf("%s\n", getenv("PWD"));
}

int	main(void)
{
	char	*str;
	t_argv	**argv;
	int		stop;
	int		w;
	
	atexit(leaks);
	stop = 1;
	argv = malloc(sizeof(t_argv *));
	while (stop != 0)
	{
		w = 0;
		*argv = NULL;
		str = readline("\033[;33mMinishell$\033[0m ");
		if (ft_strcmp(str, "exit") == 0)
			stop = 0;
		/*if (min_stop(str) == 0)
			stop = 0;*/
		add_history(str);
		arguments(argv, str);
		min_split(argv);
		print_list(argv);
		min_builtins(str, argv);
		free_arg_str(str, *argv);
	}
	free(argv);
	return (0);
}


void	print_list(t_argv **argv)
{
	t_argv	*aux;
	int		w;
	int		i;

	w = 0;
	aux = *argv;
	while (aux)
	{
		i = 0;
		//printf("arg[%d]->%p->%s\n", w, aux, aux->arg);
		
		printf("arg[%d]->%s\n", w, aux->arg);
		while (aux->split[i])
		{
			printf("\ts[%d]->%s\n", i, aux->split[i]);
			i++;
		}
		w++;
		aux = aux->next;
	}
}

