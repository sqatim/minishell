/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalHandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:43:55 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/20 18:24:45 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void handleCtrlC(int signum)
{
    if (g_global.forkFlag == 0)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        // rl_replace_line("", 0);
        rl_redisplay();
    }
    g_global.forkFlag = 0;
}

void handleCtrlBackSlash(int signum)
{
    if (g_global.forkFlag == 0)
        rl_redisplay();
    else
    {
        ft_putstr_fd("Quit: 3\n", 1);
        rl_redisplay();
    }
    g_global.forkFlag = 0;
}

void signalHandler()
{
    signal(SIGINT, handleCtrlC);
    signal(SIGQUIT, handleCtrlBackSlash);
}