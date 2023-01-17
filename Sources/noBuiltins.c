/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:21:27 by kernel            #+#    #+#             */
/*   Updated: 2023/01/17 18:59:25 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*check_command_access(t_env *env, char *command)
{
	char	*cmd_joined;
	char	*path_env;
	char	**path;
	int		index;

	index = 0;
	if (!access(command, F_OK))
		return (ft_strdup(command));
	path_env = ft_get_env(env, "PATH");
	path = ft_split(path_env, ':');
	while (path && path[index])
	{
		cmd_joined = join_path_with_command(path[index], command);
		if (!access(cmd_joined, F_OK))
		{
			free_array_two_dimension(path);
			return (cmd_joined);
		}
		free_string(cmd_joined);
		index++;
	}
	free_array_two_dimension(path);
	return (NULL);
}

char	*handle_no_builtins_command(t_execution *exec_struct, char **cmd_line)
{
	char	*command;

	command = check_command_access(exec_struct->env, cmd_line[0]);
	if (!command)
	{
		g_global.exit = 127;
		print_command_not_found(cmd_line[0]);
		return (NULL);
	}
	return (command);
}

void	handle_no_builtins(t_execution *exec_struct, char **cmd_line, \
					t_context context, int check)
{
	char	*command;
	int		pid;

	if (check)
	{
		command = handle_no_builtins_command(exec_struct, cmd_line);
		if (command)
		{
			g_global.forkFlag = 1;
			pid = fork();
			if (pid == 0)
			{
				exec_redirection(exec_struct, context);
				if (context.fd_close >= 0)
					close(context.fd_close);
				if (execve(command, cmd_line, exec_struct->envArray) == -1)
					print_error(command);
			}
			else
				free_string(command);
		}
	}
}
