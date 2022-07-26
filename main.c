/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:56:10 by potero-d          #+#    #+#             */
/*   Updated: 2022/07/26 17:29:22 by pmoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sign;

void	leaks(void)
{
	system("leaks minishell");
}

void	no_ctrlprint(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

int	execute(t_data *data)
{
	t_argv	*arg;

	arg = *data->argv;
	
	if (arg->split[0] && arg->next == 0)
	{
		if (ft_strcmp(arg->split[0], "exit") == 0)
		{
			printf("exit\n");
			return (0);
		}
	}
	command_found(data);
	if (data->num_argc == 1 && data->error_no == 0)
	{
		data->error_no = execute_cmmd(data);
		//data->error_no = pipe_execute(data);
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

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	
}

void	handler_ctrlslash(int sig)
{
	if (sign == 0 && sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sign > 0 && sig == SIGQUIT)
	{
		kill(sign, SIGCONT);
		write(2, "\n^\\Quit: 3\n", 11);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv2, char **envp)
{
	char	*str;
	t_data	data;
	int		stop;
	int		std[2];

	if (argc > 1)
		exit(1);
	argv2 = 0;
//	atexit(leaks);
	stop = 1;
	sign = 0;
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
		printf("\033[;33m");
		str = readline("\rMinishell$ ");
		printf("\033[0m");
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
