/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:58:46 by kernel            #+#    #+#             */
/*   Updated: 2022/12/04 17:00:13 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void minishellLoop(t_execution *execStruct)
{
    char *buffer;
    int size;
    char **parsedCmd;

    buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
    while (1)
    {
        // ft_putstr_fd("\033[0;32mminishell:>\033[m ", 1);
        ft_putstr_fd("minishell:> ", 1);
        size = read(0, buffer, BUFFER_SIZE);
        if (size == -1)
        {
            printf("error: read\n");
            exit(1);
        }
        buffer[size - 1] = '\0';
        parsedCmd = parseCommand(buffer);
        checkCommand(parsedCmd, execStruct);
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