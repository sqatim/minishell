/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:07 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/19 15:48:21 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	handle_exit_status_after_fork(int w_status)
{
	int	status_code;

	if (WIFEXITED(w_status))
	{
		status_code = WEXITSTATUS(w_status);
		g_global.exit = status_code;
	}
	else if (WIFSIGNALED(w_status))
	{
		if (WTERMSIG(w_status) == 3 || WTERMSIG(w_status) == 2)
		{
			if (WTERMSIG(w_status) == 3)
				write(2, "Quit: 3\n", 8);
			g_global.exit = 128 + WTERMSIG(w_status);
		}
	}
}

void	start_execution(t_execution *exec_struct, t_command *command)
{
	t_context	context;
	int			children;
	int			index;
	int			w_status;

	index = 0;
	context.fd[0] = STDIN_FILENO;
	context.fd[1] = STDOUT_FILENO;
	context.fd_close = -1;
	children = exec_command_of_node(exec_struct, command, context);
	while (index < children)
	{
		wait(&w_status);
		handle_exit_status_after_fork(w_status);
		index++;
	}
	g_global.fork_flag = 0;
	return ;
}

int	exec_pipe(t_execution *exec_struct, t_command *command, t_context context)
{
	t_pipe	pipe_struct;
	int		child;
	int		p[2];

	child = 0;
	pipe(p);
	pipe_struct.left_context = context;
	pipe_struct.left_context.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
	pipe_struct.left_context.fd_close = p[STDIN_FILENO];
	pipe_struct.left_node = clone_node(command);
	child += exec_command_of_node(exec_struct, pipe_struct.left_node, \
				pipe_struct.left_context);
	pipe_struct.left_node = free_command(pipe_struct.left_node);
	pipe_struct.right_context = context;
	pipe_struct.right_context.fd[STDIN_FILENO] = p[STDIN_FILENO];
	pipe_struct.right_context.fd_close = p[STDOUT_FILENO];
	if (command->next && command->next->command && \
		!check_type_of_command(command->next->command[0]))
		close(p[STDOUT_FILENO]);
	pipe_struct.right_node = command->next;
	child += exec_command_of_node(exec_struct, pipe_struct.right_node, \
				pipe_struct.right_context);
	close(p[STDIN_FILENO]);
	close(p[STDOUT_FILENO]);
	return (child);
}

int	exec_redirection(t_execution *exec_struct, t_context context)
{
	t_redirection	*redirection;
	int				result;

	result = 0;
	redirection = check_type_of_redirection(exec_struct->redirections_sorted, \
		0);
	if (redirection)
		result += exec_input_redirection(redirection);
	else
		dup2(context.fd[STDIN_FILENO], STDIN_FILENO);
	redirection = check_type_of_redirection(exec_struct->redirections_sorted, \
		1);
	if (redirection)
		result += exec_output_redirection(redirection);
	else
		dup2(context.fd[STDOUT_FILENO], STDOUT_FILENO);
	return (result);
}

int	exec_command_of_node(t_execution *exec_struct, \
		t_command *command, t_context context)
{
	if (command && !command->next)
		return (check_command(exec_struct, command, context));
	else if (command && command->next)
		return (exec_pipe(exec_struct, command, context));
	else
		return (0);
}
