/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:07 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/21 11:31:06 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void startExecution(t_execution *execStruct, t_command *command)
{
    t_context context;
    int children;
    int index;

    index = 0;
    context.fd[0] = STDIN_FILENO;
    context.fd[1] = STDOUT_FILENO;
    context.fd_close = -1;
    children = execCommandOfNode(execStruct, command, context);
    while (index < children)
    {
        wait(NULL);
        index++;
    }
    return;
}

int execPipe(t_execution *execStruct, t_command *command, t_context context)
{
    t_pipe pipeStruct;
    int child;
    int p[2];
    child = 0;
    pipe(p);
    pipeStruct.left_context = context;
    pipeStruct.left_context.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    pipeStruct.left_context.fd_close = p[STDIN_FILENO];
    pipeStruct.leftNode = cloneNode(command);
    // if (command->next->next)
    //     close(p[STDIN_FILENO]);

    child += execCommandOfNode(execStruct, pipeStruct.leftNode, pipeStruct.left_context);
    freeCommand(&pipeStruct.leftNode);
    pipeStruct.right_context = context;
    pipeStruct.right_context.fd[STDIN_FILENO] = p[STDIN_FILENO];
    pipeStruct.right_context.fd_close = p[STDOUT_FILENO];
    if (command->next->next && !checkTypeOfCommand(command->next->next->word_cmd[0]))
        close(p[STDOUT_FILENO]);
    pipeStruct.rightNode = command->next;
    child += execCommandOfNode(execStruct, pipeStruct.rightNode, pipeStruct.right_context);
    close(p[STDIN_FILENO]);
    close(p[STDOUT_FILENO]);
    return child;
}

int execRedirection(t_execution *execStruct, t_context context)
{
    t_redirection *redirection;
    int result;

    result = 0;
    redirection = checkTypeOfRedirection(execStruct->redirectionsSorted, 0);
    if (redirection)
    {
        // ft_putendl_fd("1", 2);
        result += execInputRedirection(redirection);
    }
    else
    {
        // ft_putnbr_fd(context.fd[STDIN_FILENO], 2);
        // ft_putendl_fd("", 2);
        dup2(context.fd[STDIN_FILENO], STDIN_FILENO);
    }
    redirection = checkTypeOfRedirection(execStruct->redirectionsSorted, 1);
    if (redirection)
    {
        // ft_putendl_fd(redirection->type, 2);
        // ft_putendl_fd(redirection->f_name, 2);
        // ft_putendl_fd("3", 2);
        result += execOutputRedirection(redirection);
    }
    else
    {
        // ft_putnbr_fd(context.fd[STDOUT_FILENO], 2);
        // ft_putendl_fd("", 2);
        dup2(context.fd[STDOUT_FILENO], STDOUT_FILENO);
    }
    // ft_putendl_fd("----------------------------", 2);
    return (result);
}

int execCommandOfNode(t_execution *execStruct, t_command *command, t_context context)
{
    if (command && !command->next)
        return checkCommand(execStruct, command, context);
    else if (command && command->next)
        return execPipe(execStruct, command, context);
    else
        return 0;
}