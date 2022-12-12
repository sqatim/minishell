/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:21:27 by kernel            #+#    #+#             */
/*   Updated: 2022/12/12 17:02:57 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char *checkCommandAccess(t_env *env, char *command)
{
    char *pathEnv;
    char **path;
    char *cmdJoined;
    int index;

    index = 0;
    if (!access(command, F_OK))
        return ft_strdup(command);
    pathEnv = ft_getEnv(env, "PATH");
    path = ft_split(pathEnv, ':');
    while (path && path[index])
    {
        cmdJoined = joinPathWithCommand(path[index], command);
        if (!access(cmdJoined, F_OK))
            return cmdJoined;
        index++;
    }
    return NULL;
}

void handleNoBuiltins(t_execution *execStruct, char **cmdLine, t_context context)
{
    char *command;
    int pid;
    command = checkCommandAccess(execStruct->env, cmdLine[0]);
    if (!command)
        printError(cmdLine[0]);
    else
    {
        g_global.forkFlag = 1;
        pid = fork();
        if (pid == 0)
        {
            dup2(context.fd[STDIN_FILENO], STDIN_FILENO);
            dup2(context.fd[STDOUT_FILENO], STDOUT_FILENO);
            if (context.fd_close >= 0)
            {
                close(context.fd_close);
            }
            execve(command, cmdLine, NULL);
        }
        else
        {
            g_global.forkFlag = 0;
            return;
        }
    }
}