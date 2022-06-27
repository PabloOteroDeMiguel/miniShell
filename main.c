/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/06/27 13:21:20 by potero           ###   ########.fr       */
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
//	int		i;

	argv = *data->argv;
	if (argv->split[0] == 0)
		return (1);
	if ((ft_strcmp(argv->split[0], "echo") == 0)
		|| (ft_strncmp(str, "ECHO", 4) == 0))
		min_echo(data->argv);
	else if (ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "PWD") == 0)
		min_pwd(data->myenv);
	else if (ft_strcmp(str, "env") == 0 || ft_strcmp(str, "ENV") == 0)
		print_env(data->myenv);
	else if (ft_strcmp(argv->split[0], "cd") == 0)
		min_cd(data);
	else if (ft_strcmp(argv->split[0], "export") == 0)
		min_export(data);
	else if (ft_strcmp(argv->split[0], "unset") == 0)
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
		command_found(data);
	
		if (data->num_argc == 1 && data->error_no == 0)
		{
			data->error_no = execute(data);
			pipe_error(data);
		}
		else if (data->num_argc > 1 && data->error_no == 0) 
		{
			data->error_no = pipe_execute(data);
			pipe_error(data);
		}
		
	}
	return (1);
}

int	cont_arg(t_argv **argv)
{
	int		cont;
	t_argv	*aux;

	cont = 0;
	aux = *argv;
	while (aux)
	{
		cont++;
		aux = aux->next;
	}
	return (cont);
}

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
	//	rl_replace_line("", 0);
		rl_redisplay();
	}
	
}
/*
void	sighandler(void)
{
	struct sigaction	ctrlc;

	ctrlc.sa_handler = &handler_ctrlc;
	sigaction(SIGINT, &ctrlc, NULL);
}
*/
int	main(int argc, char **argv2, char **envp)
{
	char	*str;
	t_data	data;
	int		stop;
	int		std[2];

	if (argc > 1)
		exit(1);
	argv2 = 0;
	//atexit(leaks);
	stop = 1;
	data.argv = malloc(sizeof(t_argv *));
	data.myenv = malloc(sizeof(t_myenv *));
	*data.myenv = 0;
//	data.infile = "/dev/fd/0";
//	data.outfile = "/dev/fd/1";
//	data.infile = "a.txt";
//	data.outfile = "b.txt";
	data.error_no = 0;
	min_getenv(envp, data.myenv);
	data.myenv_str = env_to_char(data.myenv);
	//sighandler();
	signal(SIGINT, sighandler);
	while (stop != 0)
	{
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
		*data.argv = NULL;	
		printf("\033[;33m");
		str = readline("Minishell$ ");
		printf("\033[0m");
		if (!str)
		{
			printf("exit1\n");
			exit(0);
		}
		if (str && ft_strlen(str) > 0)
		{
			set_initial_files(&data);
			add_history(str);
			arguments(data.argv, str);
			expand(&data);
			min_split(&data);
			remove_quotes(data.argv);
			data.num_argc = cont_arg(data.argv);
			check_files(&data);
			direction(&data);
			print_list(data.argv);
			printf("Infile: %s\n", data.infile);
			printf("Outfile: %s\n", data.outfile);
			stop = min_builtins(str, &data);
		}
		free_arg_str(str, *data.argv);
		dup2(STDIN_FILENO, std[0]);
		dup2(STDOUT_FILENO, std[1]);
	}
	free_env(*data.myenv);
	free_env_char(data.myenv_str);
	free(data.myenv);
	free(data.argv);
	return (0);
}
