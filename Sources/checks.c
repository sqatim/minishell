/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:50:47 by kernel            #+#    #+#             */
/*   Updated: 2022/12/24 15:50:49 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int check_type_of_command(char *str)
{
    if (!ft_strcmp(str, "env") || !ft_strcmp(str, "unset") ||
        !ft_strcmp(str, "export") || !ft_strcmp(str, "pwd") ||
        !ft_strcmp(str, "cd") || !ft_strcmp(str, "echo") ||
        !ft_strcmp(str, "exit"))
        return BUILTIN;
    return NON_BUILTIN;
}

int check_shell_lvl_value(char *argument)
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
    return type;
}

int check_command(t_execution *execStruct, t_command *command, t_context context)
{
    char **word_cmd;
    t_redirection *redirections;

    redirections = command->redirections;
    if (redirections)
        execStruct->redirections_sorted = handle_redirection(redirections);
    word_cmd = command->command;
    if (check_type_of_command(word_cmd[0]))
    {
        handle_builtin_command(execStruct, command, context);
        return 0;
    }
    else
        handle_no_builtins(execStruct, word_cmd, context);
    if (execStruct->redirections_sorted)
        free_redirection(&execStruct->redirections_sorted);
    return 1;
}