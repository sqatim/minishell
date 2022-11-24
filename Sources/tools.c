/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:58:46 by kernel            #+#    #+#             */
/*   Updated: 2022/11/24 22:37:19 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **parseCommand(char *cmdLine)
{
    char **parsedCmd;

    parsedCmd = ft_split(cmdLine, ' ');
    return parsedCmd;
}

char **setupEnv(char **envp)
{
    int index;
    char **envVariables;

    index = 0;
    while (envp[index])
        index++;
    envVariables = (char **)malloc(sizeof(char *) * (index + 1));
    // to handle ------;
    if (!envVariables)
        exit(1);
    index = 0;
    while (envp[index])
    {
        envVariables[index] = ft_strdup(envp[index]);
        index++;
    }
    return envVariables;
}

void minishellLoop(t_execution *execStruct)
{
    char *buffer;
    int size;
    char **parsedCmd;

    buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
    while (1)
    {
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