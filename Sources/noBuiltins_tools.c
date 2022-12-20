/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:37:25 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/15 17:28:00 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char *joinPathWithCommand(char *path, char *command)
{
    char *ptrToBeFreed;
    char *cmdJoined;

    cmdJoined = ft_strjoin(path, "/");
    ptrToBeFreed = cmdJoined;
    cmdJoined = ft_strjoin(cmdJoined, command);
    freeString(ptrToBeFreed);
    return cmdJoined;
}

int envLinkedListLen(t_env *env)
{
    t_env *tmp;
    int index;

    index = 0;
    tmp = env;
    while (tmp)
    {
        index++;
        tmp = tmp->next;
    }
    return (index);
}

char **convertEnvToArray(t_env *env)
{
    char **envArray;
    int index;
    int len;
    t_env *tmp;

    index = 0;
    len = envLinkedListLen(env);
    envArray = ft_calloc(++len, sizeof(char *));
    tmp = env;
    while (tmp)
    {
        envArray[index++] = ft_strdup(tmp->content);
        tmp = tmp->next;
    }
    return envArray;
}