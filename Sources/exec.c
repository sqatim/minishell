/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:07 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/26 12:38:49 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void  start_execution(t_execution *exec_struct, t_command *command)
{
    t_context context;
    int children;
    int index;
    int w_status;
    int status_code;

    index = 0;
    context.fd[0] = STDIN_FILENO;
    context.fd[1] = STDOUT_FILENO;
    context.fd_close = -1;
    children = execCommandOfNode(exec_struct, command, context);
    while (index < children)
    {
        wait(&w_status);
        if (WIFEXITED(w_status))
        {
            status_code = WEXITSTATUS(w_status);
            g_global.exit = status_code;
        }
        index++;
    }
    g_global.forkFlag = 0;
    printf("=== %d ===\n", g_global.exit);
    return;
}

int exec_pipe(t_execution *exec_struct, t_command *command, t_context context)
{
    t_pipe pipe_struct;
    int child;
    int p[2];
    
    child = 0;
    pipe(p);
    pipe_struct.left_context = context;
    pipe_struct.left_context.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    pipe_struct.left_context.fd_close = p[STDIN_FILENO];
    pipe_struct.left_node = clone_node(command);
    child += execCommandOfNode(exec_struct, pipe_struct.left_node,\
         pipe_struct.left_context);
    free_command(&pipe_struct.left_node);
    pipe_struct.right_context = context;
    pipe_struct.right_context.fd[STDIN_FILENO] = p[STDIN_FILENO];
    pipe_struct.right_context.fd_close = p[STDOUT_FILENO];
    if (command->next->next && \
        !check_type_of_command(command->next->next->command[0]))
        close(p[STDOUT_FILENO]);
    pipe_struct.right_node = command->next;
    child += execCommandOfNode(exec_struct, pipe_struct.right_node,\
         pipe_struct.right_context);
    close(p[STDIN_FILENO]);
    close(p[STDOUT_FILENO]);
    return child;
}

int execRedirection(t_execution *exec_struct, t_context context)
{
    t_redirection *redirection;
    int result;

    result = 0;
    redirection = check_type_of_redirection(exec_struct->redirections_sorted, 0);
    printRedirection(exec_struct->redirections_sorted);
    if (redirection)
        result += exec_input_redirection(redirection);
    else
        dup2(context.fd[STDIN_FILENO], STDIN_FILENO);
    redirection = check_type_of_redirection(exec_struct->redirections_sorted, 1);
    if (redirection)
        result += exec_output_redirection(redirection);
    else
        dup2(context.fd[STDOUT_FILENO], STDOUT_FILENO);
    return (result);
}

int execCommandOfNode(t_execution *exec_struct, t_command *command, t_context context)
{
    if (command && !command->next)
        return check_command(exec_struct, command, context);
    else if (command && command->next)
        return exec_pipe(exec_struct, command, context);
    else
        return 0;
}