/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:39 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/17 19:33:58 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_global	g_global;

void	disable_ctrl_chars(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	init_global_variable(void)
{
	g_global.forkFlag = 0;
	g_global.exit = 0;
	g_global.here_doc = 1;
}

int	main(int ac, char **av, char **envp)
{
	t_execution	*exec_struct;

	(void)av;
	if (ac == 1)
	{
		disable_ctrl_chars();
		init_global_variable();
		exec_struct = execution_initialization(envp);
		minishell_loop(exec_struct);
	}
	return (0);
}
