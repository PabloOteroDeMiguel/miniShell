/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:01:11 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/04 11:29:36 by potero-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_ctrlprint(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_sign == 2)
		{
			close(0);
			write(1, "\n", 1);
			exit(1);
		}
		else if (g_sign == 3)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	handler_ctrlslash(int sig)
{
	if (g_sign == 0 && sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (g_sign > 0 && sig == SIGQUIT)
	{
		kill(g_sign, SIGCONT);
		write(2, "\n^\\Quit: 3\n", 11);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\r");
	}
	g_sign = 0;
}
