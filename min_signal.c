/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoreno- <pmoreno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:01:11 by potero-d          #+#    #+#             */
/*   Updated: 2022/08/11 10:25:36 by pmoreno-         ###   ########.fr       */
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
		if (g_sign[0] == 2)
		{
			close(0);
			write(1, "\n", 1);
			g_sign[0] = 0;
			exit(1);
		}
		else if (g_sign[0] == 0)
		{
			kill(g_sign[0], SIGCONT);
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_sign[0] = 0;
		}
		else
		{
			if (g_sign[1] == 0)
			{
				kill(g_sign[0], SIGCONT);
				write(1, "^C\n", 3);
				rl_on_new_line();
				rl_replace_line("", 0);
				printf("\r");
				g_sign[0] = 0;
			}
			else
			{
				kill(g_sign[0], SIGCONT);
				write(1, "\n", 3);
				rl_on_new_line();
				rl_replace_line("", 0);
				printf("\r");
				g_sign[1] = 2;
				g_sign[0] = 0;
			}
		}
	}
}

void	ctrlslash(int sig)
{
	if (g_sign[0] == 0 && sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (g_sign[0] > 0 && sig == SIGQUIT)
	{
		kill(g_sign[0], SIGCONT);
		write(2, "^\\Quit: 3\n", 11);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\r");
	}
}
