/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalHandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:43:55 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/19 02:17:29 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	handle_ctrl_c(int signum)
{
	if (signum == SIGINT)
	{
		if (g_global.fork_flag == 0)
		{
			g_global.exit = 1;
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_global.here_doc)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
	}
}

void	signal_handler(void)
{
	if (signal(SIGINT, handle_ctrl_c) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		write(2, "sig error\n", 10);
		exit(1);
	}
}
