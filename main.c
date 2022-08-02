/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/02 13:52:43 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

void	min_exit(t_argv *arg, t_data *data)
{
	if (ft_strcmp(arg->split[0], "exit") == 0)
	{
		if (arg->split[1])
		{
			if (ft_atoi(arg->split[1]))
			{
				data->error_no = ft_atoi(arg->split[1]);
				update_error(data);
				exit (ft_atoi(arg->split[1]));
			}
			else
				printf("Minishell: exit: %s: numeric argument required",
					arg->split[1]);
		}
		printf("exit\n");
		exit (0);
	}
}

int	execute(t_data *data)
{
	t_argv	*arg;

	arg = *data->argv;
	command_found(data);
	if (data->num_argc == 1 && data->error_no == 0)
	{
		if (exception(arg, data) == 0)
			return (1);
		min_exit(arg, data);
		data->error_no = execute_cmmd(data);
		pipe_error(data);
	}
	else if (data->num_argc > 1 && data->error_no == 0)
	{
		data->error_no = pipe_execute(data);
		pipe_error(data);
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

int	main(int argc, char **argv2, char **envp)
{
	char	*str;
	int		stop;
	int		std[2];
	t_data	data;

	if (argc > 1)
		exit(1);
	argv2 = 0;
//	atexit(leaks);
	stop = 1;
	g_sign = 0;
	data.argv = malloc(sizeof(t_argv *));
	data.myenv = malloc(sizeof(t_myenv *));
	*data.myenv = 0;
	data.error_no = 0;
	min_getenv(envp, data.myenv);
	data.myenv_str = env_to_char(data.myenv);
	while (stop != 0)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, handler_ctrlslash);
		no_ctrlprint();
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
		*data.argv = NULL;	
		//str = readline("\rMinishell$ ");
		str = readline("Minishell$ ");
		if (!str)
		{
			printf("exit1\n");
			exit(0);
		}
		if (str && ft_strlen(str) > 0)
		{
			add_history(str);
			arguments(data.argv, str);
			set_initial_files(&data);
			expand(&data);
			min_split(&data);
			remove_quotes(data.argv);
			data.num_argc = cont_arg(data.argv);
			check_files(&data);
			direction(&data);
			print_list(data.argv);
			stop = execute(&data);
		}
		free_arg_str(str, *data.argv);
		dup2(STDIN_FILENO, std[0]);
		dup2(STDOUT_FILENO, std[1]);
		unlink(".here_doc");
	}
	free_env(*data.myenv);
	free_env_char(data.myenv_str);
	free(data.myenv);
	free(data.argv);
	return (0);
}
