/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:50:47 by kernel            #+#    #+#             */
/*   Updated: 2022/12/04 17:00:13 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
        handleNoBuiltins(execStruct, cmdLine);
}