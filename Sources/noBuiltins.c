/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:21:27 by kernel            #+#    #+#             */
/*   Updated: 2022/12/07 11:24:19 by kernel           ###   ########.fr       */
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

void handleNoBuiltins(t_execution *execStruct, char **cmdLine)
{
    char *command;
    int pid;
    command = checkCommandAccess(execStruct->env, cmdLine[0]);
    if (!command)
        printError(cmdLine[0]);
    else
    {
        pid = fork();
        if (pid == 0)
        {
            execve(command, cmdLine, NULL);
        }
        else
        {
            wait(NULL);
        }
    }
    // int id = fork();
    // char cmd[] = "ls";
    // char *argVec[] = {"ls", NULL};
    // char *envVec[] = {"PATH=/bin"};
    // if (id == 0)
    // {
    //     // printf("wa fen a ba\n");
    //     if(execve(cmd, argVec, envVec) == -1)
    //         printError(cmd);
    // }
    // else
    // {
    //     wait(NULL);
    // }
}