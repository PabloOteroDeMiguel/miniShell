/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: potero-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/05/11 12:01:10 by potero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	min_builtins(char *str, t_data *data)
{
	t_argv	*argv;
	char	**exec;
	int 	i;

	argv = *data->argv;
	if (argv->split[0] == 0)
		return (1);
	if ((ft_strcmp(argv->split[0], "echo") == 0) || (ft_strncmp(str, "ECHO", 4) == 0))
		min_echo(data->argv);
	else if (ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "PWD") == 0)
		min_pwd(data->myenv);
	else if (ft_strcmp(str, "env") == 0 || ft_strcmp(str, "ENV") == 0)
		print_env(data->myenv);
	else if	(ft_strcmp(argv->split[0], "cd") == 0)
		min_cd(data);
	else if (ft_strcmp(argv->split[0], "export") == 0)
		min_export(data);
	else if	(ft_strcmp(argv->split[0], "unset") == 0)
		min_unset(data->myenv, *data->argv);
	//else if (ft_strcmp(argv->split[0], "./minishell") == 0)
	//	execve("minishell", 0, 0);
	else if (ft_strcmp(argv->split[0], "exit") == 0)
	{
			printf("exit\n");
			return (0);
	}
	else
	{
		exec = malloc(sizeof(char *) * 4);
		exec[0] = data->infile;
		exec[1] = argv->arg;
		exec[2] = data->outfile;
		exec[3] = 0;
		i = command(exec, data->myenv_str);
		printf("%i\n", i);
		free(exec);
	} 	
	return (1);
}

int	main(int argc, char **argv2, char **envp)
{
	char	*str;
	t_data	data;
	int		stop;
	int		w;
//	int i = 0;
	
	if (argc > 1) 
		exit(1);
	argv2 = 0;
	atexit(leaks);
	stop = 1;
	data.argv = malloc(sizeof(t_argv *));
	data.myenv = malloc(sizeof(t_myenv *));
	*data.myenv = 0;
	data.infile = "/dev/fd/0";
	data.outfile = "/dev/fd/1";
//	data.infile = "a.txt";
//	data.outfile = "b.txt";

	min_getenv(envp, data.myenv);
	data.myenv_str = env_to_char(data.myenv);
/*
	while (data.myenv_str[i])
	{
		printf("myenv->%s\n", data.myenv_str[i]);
		printf("env--->%s\n", envp[i]);
		i++;
	}
*/
	while (stop != 0)
	{
		w = 0;
		*data.argv = NULL;	
		printf("\033[;33m");
		//str = readline("\033[;33mMinishell$ \033[0m");
		str = readline("Minishell$ ");
		printf("\033[0m");
		//printf("\033[0;32m");
		if (!str)
		{
			printf("exit\n");
			exit(0);
		}
		if (str  && ft_strlen(str) > 0)
		{
			add_history(str);
			arguments(data.argv, str);
			min_split(data.argv);
		//	print_list(data.argv);
			expand(&data);
		//	print_list(data.argv);
			stop = min_builtins(str, &data);
		}
		free_arg_str(str, *data.argv);
	}
	free_env(*data.myenv);
	free_env_char(data.myenv_str);
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
		if (aux->split[i] == 0)
			return ;
		while (aux->split[i])
		{
			printf("\ts[%d]->%s\n", i, aux->split[i]);
		//	printf("\ts[%d]->%p\n", i, aux->split[i]);
			i++;
		}
		w++;
		aux = aux->next;
	}
}
