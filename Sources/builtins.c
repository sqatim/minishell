/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:47:37 by kernel            #+#    #+#             */
/*   Updated: 2022/12/07 13:54:31 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void executeEnv(t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (tmp->display)
            ft_putendl_fd(tmp->content, 1);
        tmp = tmp->next;
    }
}

t_env *executeUnset(t_env *env, char *argument)
{
    t_env *tmp;
    t_env *next;
    char *tmpArgument;

    if (argument)
    {
        tmpArgument = ft_strjoin(argument, "=");
        tmp = env;
        while (tmp)
        {
            if (ft_strnstr(tmp->content, tmpArgument, ft_strlen(tmpArgument)))
            {
                next = tmp->next;
                if (tmp->prev)
                    tmp->prev->next = tmp->next;
                if (tmp->next)
                    tmp->next->prev = tmp->prev;
                free(tmp->content);
                free(tmp);
                tmp = NULL;
                tmp = next;
                break;
            }
            else
                tmp = tmp->next;
        }
        if (tmp && !tmp->prev)
            env = tmp;
        free(tmpArgument);
        tmpArgument = NULL;
    }
    return env;
}

t_env *executeExport(t_env *env, char **argument)
{
    if (!argument[1])
        printEnvWithExport(env);
    else
        env = handleExport(env, argument);
    return env;
}

void executePwd()
{
    char buffer[1024];

    if (getcwd(buffer, 1024))
        ft_putendl_fd(buffer, 1);
    else
        ft_putendl_fd("error: in pwd", 2);
    // to handle --------------
}

void executeCd(t_env *env, char **argument)
{
    char *path;

    if (!argument[1])
        changeDirectory(env, NULL);
    else
        changeDirectory(env, argument[1]);
}

void executeEcho(char **argument)
{
    int indexOne;
    int check;

    indexOne = 1;
    check = handleNewLineInEcho(argument, &indexOne);
    while (argument[indexOne])
    {
        ft_putstr_fd(argument[indexOne], 1);
        if (argument[indexOne + 1])
            ft_putchar_fd(' ', 1);
        indexOne++;
    }
    if (check == 0)
        ft_putchar_fd('\n', 1);
}

void executeExit(char **argument)
{
    int type;
    unsigned long long number;

    if (!argument[1])
    {
        // to handle ---- Will exit with status of last command
    }
    else
    {
        type = checkExitArgumentType(argument[1]);
        if (type == 0)
            printExitError(2, argument[1]);
        else
            handleExitCases(type, argument);
    }
}