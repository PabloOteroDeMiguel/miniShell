/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/04/04 10:45:02 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

void	min_builtins(char *str, t_data *data)
{
	t_argv	*argv;

	argv = *data->argv;
	if ((ft_strcmp(argv->split[0], "echo") == 0) || (ft_strncmp(str, "ECHO", 4) == 0))
		min_echo(data->argv);
	else if (ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "PWD") == 0)
		min_pwd(data->myenv);
	else if (ft_strcmp(str, "env") == 0 || ft_strcmp(str, "ENV") == 0)
		print_env(data->myenv);
	else if	(ft_strcmp(argv->split[0], "cd") == 0)
		min_cd(data);
}

int	main(int argc, char **argv2, char **envp)
{
	char	*str;
	t_data	data;
	int		stop;
	int		w;
	
	if (envp)
		;
	if (argc > 1) 
		exit(1);
	argv2 = 0;
	atexit(leaks);
	stop = 1;
	data.argv = malloc(sizeof(t_argv *));
	data.myenv = malloc(sizeof(t_myenv *));
	*data.myenv = 0;
	min_getenv(envp, data.myenv);
	while (stop != 0)
	{
		w = 0;
		*data.argv = NULL;
		str = readline("\033[;33mMinishell$\033[0m ");
		if (ft_strcmp(str, "exit") == 0)
			stop = 0;
		add_history(str);
		arguments(data.argv, str);
		min_split(data.argv);
		//print_list(data.argv);
		min_builtins(str, &data);
		free_arg_str(str, *data.argv);
	}
	free_env(*data.myenv);
	free(data.myenv);
	free(data.argv);
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

