/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:50:47 by kernel            #+#    #+#             */
/*   Updated: 2022/12/07 15:42:24 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void checkCommand(char **cmdLine, t_execution *execStruct)
{
    if (!ft_strcmp(cmdLine[0], "env"))
        executeEnv(execStruct->env);
    else if (!ft_strcmp(cmdLine[0], "unset"))
        execStruct->env = executeUnset(execStruct->env, cmdLine[1]);
    else if (!ft_strcmp(cmdLine[0], "export"))
        execStruct->env = executeExport(execStruct->env, cmdLine);
    else if (!ft_strcmp(cmdLine[0], "pwd"))
        executePwd();
    else if (!ft_strcmp(cmdLine[0], "cd"))
        executeCd(execStruct->env, cmdLine);
    else if (!ft_strcmp(cmdLine[0], "echo"))
        executeEcho(cmdLine);
    else if (!ft_strcmp(cmdLine[0], "exit"))
        executeExit(cmdLine);
    else
        handleNoBuiltins(execStruct, cmdLine);
}