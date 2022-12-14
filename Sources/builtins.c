/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:47:37 by kernel            #+#    #+#             */
/*   Updated: 2022/12/14 16:33:09 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void executeEnv(t_execution *execStruct, t_env *env)
{
    t_env *tmp;

    tmp = env;
    // ft_putendl_fd("testo", 2);
    while (tmp)
    {
        if (tmp->display)
            ft_putendl_fd(tmp->content, 1);
        tmp = tmp->next;
    }
}

t_env *executeUnset(t_execution *execStruct, t_env *env, char *argument)
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
                // printf("------------%s\n", tmp->content);
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

t_env *executeExport(t_execution *execStruct, t_env *env, char **argument)
{
    if (!argument[1])
        printEnvWithExport(execStruct, env);
    else
        env = handleExport(execStruct, env, argument);
    return env;
}

void executePwd(t_execution *execStruct)
{
    char buffer[1024];

    if (getcwd(buffer, 1024))
    {

        ft_putendl_fd(buffer, 1);
        // ft_putendl_fd("vayne", 2);
    }
    else
        ft_putendl_fd("error: in pwd", 2);
    // to handle --------------
}

void executeCd(t_execution *execStruct, t_env *env, char **argument)
{
    char *path;

    if (!argument[1])
        changeDirectory(env, NULL);
    else
        changeDirectory(env, argument[1]);
}

void executeEcho(t_execution *execStruct, char **argument)
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

void executeExit(t_execution *execStruct, char **argument)
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

void handleBuiltinCommand(t_execution *execStruct, t_command *command, t_context context)
{
    char **word_cmd;
    int stdOut;
    int stdIn;
    int result;

    word_cmd = command->word_cmd;
    stdOut = dup(STDOUT_FILENO);
    stdIn = dup(STDIN_FILENO);
    result = execRedirection(execStruct, context);
    // dup2(context.fd[STDIN_FILENO], STDIN_FILENO);
    // dup2(context.fd[STDOUT_FILENO], STDOUT_FILENO);
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
    if (context.fd[STDOUT_FILENO] != STDOUT_FILENO || context.fd[STDIN_FILENO] != STDIN_FILENO || result)
    {
        if (context.fd[STDIN_FILENO] == STDIN_FILENO || result == 1 || result == 3)
            dup2(stdOut, STDOUT_FILENO);
        if (context.fd[STDOUT_FILENO] == STDOUT_FILENO || result == 2 || result == 3)
            dup2(stdIn, STDIN_FILENO);
        close(stdOut);
        close(stdIn);
    }
    // if (context.fd >= 0)
    // {
        // close(context.fd_close);
    // }
    // else if (context.fd[STDOUT_FILENO] == STDOUT_FILENO && context.fd[STDIN_FILENO] != STDIN_FILENO)
    // {
    //     dup2(stdIn, STDIN_FILENO);
    //     close(stdOut);
    //     close(stdIn);
    // } // ft_putendl_fd("dont say that", 2);
}