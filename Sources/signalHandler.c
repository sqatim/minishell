/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalHandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:43:55 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/17 19:32:17 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	handle_ctrl_c(int signum)
{
	(void)signum;
	if (g_global.forkFlag == 0)
	{
		if (g_global.here_doc == 1)
		{
			g_global.exit = 1;
			g_global.here_doc = 0;
		}
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_global.forkFlag = 0;
}

void	handle_ctrl_back_slash(int signum)
{
	(void)signum;
	if (g_global.forkFlag == 0)
		rl_redisplay();
	else
	{
		ft_putstr_fd("Quit: 3\n", 1);
		rl_redisplay();
	}
	g_global.forkFlag = 0;
}

void	signal_handler(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_back_slash);
}
