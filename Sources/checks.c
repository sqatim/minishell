/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:50:47 by kernel            #+#    #+#             */
/*   Updated: 2022/12/09 19:24:13 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void printRedirections(t_redirection *redirections)
{
    t_redirection *print = redirections;

    while (print)
    {
        printf("%s %s\n", print->type, print->f_name);
        print = print->next;
    }
}

void checkCommand(t_execution *execStruct, t_command *command)
{
    char **word_cmd;
    t_redirection *redirections;

    redirections = execStruct->command->redirections;
    word_cmd = execStruct->command->word_cmd;
    if (execStruct->command->redirections)
    {
        execStruct->redirectionsSorted = handleRedirection(redirections);
        // printRedirections(execStruct->redirectionsSorted);
    }
    if (!ft_strcmp(word_cmd[0], "env"))
        executeEnv(execStruct, execStruct->env);
    else if (!ft_strcmp(word_cmd[0], "unset"))
        execStruct->env = executeUnset(execStruct, execStruct->env, word_cmd[1]);
    else if (!ft_strcmp(word_cmd[0], "export"))
        execStruct->env = executeExport(execStruct, execStruct->env, word_cmd);
    else if (!ft_strcmp(word_cmd[0], "pwd"))
        executePwd(execStruct);
    else if (!ft_strcmp(word_cmd[0], "cd"))
        executeCd(execStruct, execStruct->env, word_cmd);
    else if (!ft_strcmp(word_cmd[0], "echo"))
        executeEcho(execStruct, word_cmd);
    else if (!ft_strcmp(word_cmd[0], "exit"))
        executeExit(execStruct, word_cmd);
    else
        handleNoBuiltins(execStruct, word_cmd);
}