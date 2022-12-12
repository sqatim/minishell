/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:07 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/12 18:34:52 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void printTwichiya(char *str, int number)
{
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": ", 2);
    ft_putnbr_fd(number, 2);
    ft_putendl_fd("", 2);
}
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
    // ft_putstr_fd("children => ", 2);
    // ft_putnbr_fd(children, 2);
    // ft_putendl_fd("", 2);
    // ft_putendl_fd("no way\n", 2);
    // printTwichiya("children", children);
    while (index < children)
    {
        wait(NULL);
        index++;
    }
    // ft_putendl_fd("no way\n", 2);
    return;
}

int execPipe(t_execution *execStruct, t_command *command, t_context context)
{
    t_pipe pipeStruct;
    int child;
    int p[2];
    // ft_putendl_fd("WHY", 2);
    child = 0;
    pipe(p);
    // printf("p => %d\n", p[0]);
    // printf("p => %d\n", p[1]);
    pipeStruct.left_context = context;
    pipeStruct.left_context.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    pipeStruct.left_context.fd_close = p[STDIN_FILENO];
    pipeStruct.leftNode = cloneNode(command);

    child += execCommandOfNode(execStruct, pipeStruct.leftNode, pipeStruct.left_context);
    //TODO: free left Node
    pipeStruct.right_context = context;
    pipeStruct.right_context.fd[STDIN_FILENO] = p[STDIN_FILENO];
    pipeStruct.right_context.fd_close = p[STDOUT_FILENO];
    if(command->next->next)
        close(p[STDOUT_FILENO]);
    pipeStruct.rightNode = command->next;
    child += execCommandOfNode(execStruct, pipeStruct.rightNode, pipeStruct.right_context);
    close(p[STDIN_FILENO]);
    close(p[STDOUT_FILENO]);
    return child;
}

int execCommandOfNode(t_execution *execStruct, t_command *command, t_context context)
{
    if (command && !command->next)
    {
        // ft_putendl_fd("            simple", 2);
        return checkCommand(execStruct, command, context);
    }
    else if (command && command->next)
    {
        // ft_putendl_fd("pipe", 2);
        return execPipe(execStruct, command, context);
    }
    else
    {
        // ft_putendl_fd("NULL", 2);
        return 0;
    }
}