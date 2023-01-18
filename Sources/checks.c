/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:50:47 by kernel            #+#    #+#             */
/*   Updated: 2023/01/18 21:39:05 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	check_type_of_command(char *str)
{
	if (!ft_strcmp(str, "env") || !ft_strcmp(str, "unset") || \
		!ft_strcmp(str, "export") || !ft_strcmp(str, "pwd") || \
		!ft_strcmp(str, "cd") || !ft_strcmp(str, "echo") || \
		!ft_strcmp(str, "exit"))
		return (BUILTIN);
	return (NON_BUILTIN);
}

int	check_shell_lvl_value(char *argument)
{
	int	index;
	int	type;
	int	len;

	len = 0;
	index = 0;
	type = 1;
	if (argument[index] == '-' || argument[index] == '+')
	{
		if (argument[index == '-'])
			type = -1;
		index++;
		if (!argument[index])
			return (0);
	}
	while (argument[index])
	{
		if (!ft_isdigit(argument[index]))
			return (0);
		index++;
		len++;
	}
	return (type);
}

int	check_command(t_execution *exec_struct, t_command *command, \
				t_context context)
{
	t_redirection	*redirections;
	int				check;

	check = 1;
	redirections = command->redirections;
    if(redirections)
    {
        if(check_input_redirection(redirections, &check))
            exec_struct->redirections_sorted = setup_the_last_redirections(redirections);
    }
	if (command->command && g_global.here_doc == 0)
	{
		if (check_type_of_command(command->command[0]))
		{
			handle_builtin_command(exec_struct, command, context, check);
			if (exec_struct->redirections_sorted)
            {
				exec_struct->redirections_sorted = \
				free_redirection(exec_struct->redirections_sorted);
            }
			return (0);
		}
		else
			handle_no_builtins(exec_struct, command->command, context, check);
		if (exec_struct->redirections_sorted)
			exec_struct->redirections_sorted = \
			free_redirection(exec_struct->redirections_sorted);
	}
    else
        g_global.here_doc = 0;
	return (check);
}
