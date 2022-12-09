/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:58:46 by kernel            #+#    #+#             */
/*   Updated: 2022/12/09 11:52:51 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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

void handleCtrlC(int signum)
{
    if (g_global.forkFlag == 0)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    g_global.forkFlag = 0;
}

void handleCtrlBackSlash(int signum)
{
    if (g_global.forkFlag == 0)
        rl_redisplay();
    else
    {
        ft_putstr_fd("Quit: 3\n",1);
        rl_redisplay();
    }
    g_global.forkFlag = 0;
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
    // ft_putchar_fd(8, 1);
    return 0;
}

void manageCommand(t_execution *execStruct, char *buffer, int size)
{
    char **parsedCmd;

    parsedCmd = parseCommand(buffer);
    checkCommand(parsedCmd, execStruct);
    return;
}

void minishellLoop(t_execution *execStruct)
{
    char *buffer;
    char *bufferJoined;
    int size;
    t_command *command;

    // command = ft_calloc(1, sizeof(t_command));
    bufferJoined = NULL;
    signal(SIGINT, handleCtrlC);
    signal(SIGQUIT, handleCtrlBackSlash);
    // signal(SIGQUIT, handleCtrlC);
    while (1)
    {
        buffer = readline("minishell:> ");
        if (!buffer)
            exit(1);
        if (buffer[0] != '\0')
        {
            add_history(buffer);
            manageCommand(execStruct, buffer, size);
            freeString(buffer);
            buffer = NULL;
        }
    }
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