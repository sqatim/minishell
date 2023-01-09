/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalHandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 12:43:55 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/01 15:41:45 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

// void handle_ctrl_c(int signum)
// {
//     (void) signum;
//     if (g_global.forkFlag == 0)
//     {
//         write(1, "\n", 1);
//         rl_on_new_line();
//         // rl_replace_line("", 0);
//         rl_redisplay();
//     }
//     // g_global.forkFlag = 0;
// }

// void handle_ctrl_back_slash(int signum)
// {
//     (void) signum;
//     if (g_global.forkFlag == 0)
//         rl_redisplay();
//     else
//     {
//         ft_putstr_fd("Quit: 3\n", 1);
//         rl_redisplay();
//     }
//     g_global.forkFlag = 0;
// }

void signalHandler()
{
    // signal(SIGINT, handle_ctrl_c);
    // signal(SIGQUIT, handle_ctrl_back_slash);
}