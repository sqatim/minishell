/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:21:27 by kernel            #+#    #+#             */
/*   Updated: 2022/12/16 13:05:36 by kernel           ###   ########.fr       */
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

void duplicateFunction(t_context context, t_execution *execStruct)
{
    t_redirection *input;
    t_redirection *output;
    int fdInput;
    int fdOutput;
    char *path;

    input = checkTypeOfRedirection(execStruct->redirectionsSorted, 0);
    output = checkTypeOfRedirection(execStruct->redirectionsSorted, 1);
    if (input)
    {
        if (!ft_strcmp(input->type, "<<"))
        {
            path = ft_strjoin("/tmp/", input->f_name);
            fdInput = open(path, O_RDWR, 0777);
            freeString(path);
            path = NULL;
        }
        else
            fdInput = open(input->f_name, O_RDWR, 0777);
        dup2(fdInput, STDIN_FILENO);
    }
    else
        dup2(context.fd[STDIN_FILENO], STDIN_FILENO);
    if (output)
    {
        if (!ft_strcmp(output->type, ">>"))
            fdOutput = open(output->f_name, O_CREAT | O_APPEND | O_RDWR, 0777);
        else
            fdOutput = open(output->f_name, O_CREAT | O_TRUNC | O_RDWR, 0777);
        dup2(fdOutput, STDOUT_FILENO);
    }
    else
        dup2(context.fd[STDOUT_FILENO], STDOUT_FILENO);
}



void handleNoBuiltins(t_execution *execStruct, char **cmdLine, t_context context)
{
    char *command;
    int pid;
    char **env;

    command = checkCommandAccess(execStruct->env, cmdLine[0]);
    if (!command)
        printError(cmdLine[0]);
    else
    {
        g_global.forkFlag = 1;
        env = convertEnvToArray(execStruct->env);
        // ft_putendl_fd("no way",2);
        pid = fork();
        if (pid == 0)
        {
            execRedirection(execStruct, context);
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