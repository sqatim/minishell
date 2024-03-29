/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:39 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/19 02:17:29 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_global	g_global;

void	init_global_variable(void)
{
	g_global.fork_flag = 0;
	g_global.exit = 0;
	g_global.here_doc = 0;
	g_global.error = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_execution	*exec_struct;

	(void)av;
	if (ac == 1)
	{
		init_global_variable();
		exec_struct = execution_initialization(envp);
		minishell_loop(exec_struct);
	}
	return (0);
}
