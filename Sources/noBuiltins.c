/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:21:27 by kernel            #+#    #+#             */
/*   Updated: 2022/12/24 15:50:11 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char *check_command_access(t_env *env, char *command)
{
    char *path_env;
    char **path;
    char *cmd_joined;
    int index;

    index = 0;
    if (!access(command, F_OK))
        return ft_strdup(command);
    path_env = ft_get_env(env, "PATH");
    path = ft_split(path_env, ':');
    while (path && path[index])
    {
        cmd_joined = join_path_with_command(path[index], command);
        if (!access(cmd_joined, F_OK))
            return cmd_joined;
        index++;
    }
    return NULL;
}

void handle_no_builtins(t_execution *exec_struct, char **cmd_line, t_context context)
{
    char *command;
    int pid;
    char **env;

    command = check_command_access(exec_struct->env, cmd_line[0]);
    if (!command)
    {
        g_global.exit = 127;
        print_error(cmd_line[0]);
    }
    else
    {
        g_global.forkFlag = 1;
        env = convert_env_to_array(exec_struct->env);
        pid = fork();
        if (pid == 0)
        {
            execRedirection(exec_struct, context);
            if (context.fd_close >= 0)
                close(context.fd_close);
            execve(command, cmd_line, env);
        }
        else
        {
            return;
        }
    }
}