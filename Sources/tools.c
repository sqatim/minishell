/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:58:46 by kernel            #+#    #+#             */
/*   Updated: 2022/12/22 23:57:03 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void ft_exit(t_execution *execStruct)
{
    freeExecutionStruct(execStruct);
    exit(0);
}

char **parseCommand(char *cmdLine)
{
    char **parsedCmd;

    parsedCmd = ft_split(cmdLine, ' ');
    return parsedCmd;
}

t_env *setupEnv(char **envp)
{
    int index;
    t_env *env;

    env = NULL;
    index = 0;
    while (envp[index])
    {
        env = addEnvNode(env, envp[index], 1);
        index++;
    }
    return env;
}

int manageEndOfFile(char *buffer, char **bufferJoined, int size)
{
    char *ptrToBeFreed;

    ptrToBeFreed = *bufferJoined;
    buffer[size] = '\0';
    if (size == 0)
        exit(0);
    if (!(*bufferJoined))
        *bufferJoined = ft_strjoin("", buffer);
    else
    {
        *bufferJoined = ft_strjoin(*bufferJoined, buffer);
        freeString(ptrToBeFreed);
    }
    return 0;
}

void manageCommand(t_execution *execStruct, char *buffer)
{
    t_command *tmpCommand;

    startExecution(execStruct, execStruct->command);
    return;
}

void minishellLoop(t_execution *execStruct)
{
    char *buffer;
    char *bufferJoined;

    bufferJoined = NULL;
    signalHandler();
    while (1)
    {
        buffer = readline("minishell:> ");
        if (!buffer)
            ft_exit(execStruct);
        // exit(1);
        if (buffer[0] != '\0')
        {
            execStruct->command = startParse(execStruct->env, buffer);
            // execStruct->command = customizeMyParse(buffer);
            add_history(buffer);
            manageCommand(execStruct, buffer);
            freeString(buffer);
            buffer = NULL;
            freeCommand(&execStruct->command);
            freeRedirection(&execStruct->redirectionsSorted);
        }
    }
}

t_env *ft_getEnvNode(t_env *env, char *key)
{
    t_env *tmp;
    int index;
    char *tmpKey;

    tmp = env;
    tmpKey = ft_strjoin(key, "=");
    index = 0;
    while (tmp)
    {
        if (ft_strnstr(tmp->content, tmpKey, ft_strlen(tmpKey)))
        {
            while (tmp->content[index] != '=')
                index++;
            freeString(tmpKey);
            return (tmp);
        }
        tmp = tmp->next;
    }
    return NULL;
}

char *ft_getEnv(t_env *env, char *key)
{
    t_env *tmp;
    int index;
    char *tmpKey;

    tmp = env;
    tmpKey = ft_strjoin(key, "=");
    index = 0;
    while (tmp)
    {
        if (ft_strnstr(tmp->content, tmpKey, ft_strlen(tmpKey)))
        {
            while (tmp->content[index] != '=')
                index++;
            freeString(tmpKey);
            return (&tmp->content[++index]);
        }
        tmp = tmp->next;
    }
    return NULL;
}

int checkExitArgumentType(char *argument)
{
    int index;
    int type;
    int len;

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
            return 0;
        index++;
        len++;
    }
    if (len > 19)
        return (0);
    return type;
}