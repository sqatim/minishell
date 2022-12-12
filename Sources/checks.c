/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:50:47 by kernel            #+#    #+#             */
/*   Updated: 2022/12/12 18:35:00 by sqatim           ###   ########.fr       */
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

static int checkTypeOfCommand(char *str)
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

    // redirections = execStruct->command->redirections;
    // if (execStruct->command->redirections)
    //     execStruct->redirectionsSorted = handleRedirection(redirections);
    word_cmd = command->word_cmd;
    if (checkTypeOfCommand(word_cmd[0]))
    {
        handleBuiltinCommand(execStruct, command, context);
        return 0;
    }
    else
    {
        // ft_putendl_fd("why",2);
        handleNoBuiltins(execStruct, word_cmd, context);
    }
    return 1;
}