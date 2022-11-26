/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:50:47 by kernel            #+#    #+#             */
/*   Updated: 2022/11/26 20:37:50 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void checkCommand(char **cmdLine, t_execution *execStruct)
{
    if (ft_strnstr("env", cmdLine[0], 3))
        executeEnv(execStruct->env);
    else if (ft_strnstr("unset", cmdLine[0], 5))
        execStruct->env = executeUnset(execStruct->env, cmdLine[1]);
    else if (ft_strnstr("export", cmdLine[0], 6))
        execStruct->env = executeExport(execStruct->env, cmdLine);
    else if (ft_strnstr("pwd", cmdLine[0], 3))
        executePwd();
    else if (ft_strnstr("cd", cmdLine[0], 2))
        executeCd(execStruct->env, cmdLine);
    else if (ft_strnstr("echo", cmdLine[0], 4))
        executeEcho(cmdLine);
    else if (ft_strnstr("exit", cmdLine[0], 4))
        executeExit(cmdLine);
    else
        printf("no Builtins command\n");
}

int checkExitNumber(char *str)
{
    int index;
    int type; //  check if negatif or positif;
    char *number;

    index = 0;
    if (str[index++] == '-')
        type = 1;
    if (!str[index])
        return (-1);
    while (str[index])
    {
        if (!ft_isdigit(str[index]))
            return (-1);
        index++;
    }
    if (index == 0)
    {
        number = ft_lltoa(LLONG_MAX);
        if(ft_strcmp(str, number) > 0)
            return GREATER_THAN_MAXLONG;
    }
    else
    {
        number = ft_lltoa(LLONG_MIN);
        // if(ft_strcmp(str, number) > 0)
    }
    return 1;
}