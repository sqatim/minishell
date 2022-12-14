/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:50:47 by kernel            #+#    #+#             */
/*   Updated: 2022/12/14 16:35:27 by sqatim           ###   ########.fr       */
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

int checkTypeOfCommand(char *str)
{
    if (!ft_strcmp(str, "env") || !ft_strcmp(str, "unset") ||
        !ft_strcmp(str, "export") || !ft_strcmp(str, "pwd") ||
        !ft_strcmp(str, "cd") || !ft_strcmp(str, "echo") ||
        !ft_strcmp(str, "exit"))
        return BUILTIN;
    return NON_BUILTIN;
}

int checkCommand(t_execution *execStruct, t_command *command, t_context context)
{
    char **word_cmd;
    t_redirection *redirections;

    redirections = command->redirections;
    if (redirections)
        execStruct->redirectionsSorted = handleRedirection(redirections);
    word_cmd = command->word_cmd;
    if (checkTypeOfCommand(word_cmd[0]))
    {
        handleBuiltinCommand(execStruct, command, context);
        return 0;
    }
    else
        handleNoBuiltins(execStruct, word_cmd, context);
    if (execStruct->redirectionsSorted)
        freeRedirection(&execStruct->redirectionsSorted);
    return 1;
}