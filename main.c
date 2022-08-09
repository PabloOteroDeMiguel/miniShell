/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/09 11:17:04 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//atexit(leaks);
//print_list(data->argv);
/*
void	leaks(void)
{
	system("leaks minishell");
}
*/
int	execute(t_data *data)
{
	t_argv	*arg;

	arg = *data->argv;
	command_found(data);
	if (data->num_argc == 1 && data->error_no == 0)
	{
		if (exception(arg, data) == 0)
		{
			update_error(data);
			return (1);
		}
		min_exit(arg, data);
		data->error_no = execute_cmmd(data);
		update_error(data);
	}
	else if (data->num_argc > 1)
	{
		data->error_no = pipe_execute(data);
		update_error(data);
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

static void	main_part(char *str, t_data *data, int *stop)
{
	if (str && ft_strlen(str) > 0)
	{			
		signal(SIGQUIT, handler_ctrlslash);
		add_history(str);
		arguments(data->argv, str);
		set_initial_files(data);
		expand(data);
		min_split(data);
		data->num_argc = cont_arg(data->argv);
		check_files(data);
		direction(data);
		first_chr_pipe(str, *data->argv);
		*stop = execute(data);
	}
	free_arg_str(str, *data->argv);
	unlink(".here_doc");
}

static int	str_line(t_data *data)
{
	char	*str;
	int		stop;
	int		std[2];

	stop = 1;
	no_ctrlprint();
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	*data->argv = NULL;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	str = readline("Minishell$ ");
	if (!str)
	{
		printf("exit\n");
		exit(0);
	}
	main_part(str, data, &stop);
	dup2(STDIN_FILENO, std[0]);
	dup2(STDOUT_FILENO, std[1]);
	return (stop);
}

int	main(int argc, char **argv2, char **envp)
{
	int		stop;
	t_data	data;

	if (argc > 1)
		exit(1);
	argv2 = 0;
	stop = 1;
	g_sign = 0;
	data.argv = malloc(sizeof(t_argv *));
	data.myenv = malloc(sizeof(t_myenv *));
	*data.myenv = 0;
	data.error_no = 0;
	min_getenv(envp, data.myenv);
	data.myenv_str = env_to_char(data.myenv);
	while (stop != 0)
		stop = str_line(&data);
	free_env(*data.myenv);
	free_env_char(data.myenv_str);
	free(data.myenv);
	free(data.argv);
	return (0);
}
