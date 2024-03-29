/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:47:37 by kernel            #+#    #+#             */
/*   Updated: 2023/01/18 12:49:34 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	execute_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->display)
			ft_putendl_fd(tmp->content, 1);
		tmp = tmp->next;
	}
	g_global.exit = 0;
}

int	unset_itterator(t_env **tmp, char *tmp_argument)
{
	t_env	*next;
	int		check;

	check = 1;
	while (*tmp)
	{
		if (!ft_strcmp((*tmp)->name, tmp_argument))
		{
			next = (*tmp)->next;
			if ((*tmp)->prev)
				(*tmp)->prev->next = (*tmp)->next;
			if ((*tmp)->next)
				(*tmp)->next->prev = (*tmp)->prev;
			if (!(*tmp)->prev && !(*tmp)->next)
				check = 0;
			free_env_node_content(*tmp);
			free(*tmp);
			*tmp = NULL;
			*tmp = next;
			return (check);
		}
		else
			*tmp = (*tmp)->next;
	}
	return (check);
}

void	select_builtins_command(t_execution *exec_struct, t_command *command)
{
	char	**word_cmd;

	word_cmd = command->command;
	if (!ft_strcmp(word_cmd[0], "env"))
		execute_env(exec_struct->env);
	else if (!ft_strcmp(word_cmd[0], "unset"))
		exec_struct->env = execute_unset(exec_struct, exec_struct->env, \
										word_cmd);
	else if (!ft_strcmp(word_cmd[0], "export"))
		exec_struct->env = execute_export(exec_struct, exec_struct->env, \
										word_cmd);
	else if (!ft_strcmp(word_cmd[0], "pwd"))
		execute_pwd(exec_struct);
	else if (!ft_strcmp(word_cmd[0], "cd"))
		execute_cd(exec_struct, exec_struct->env, word_cmd);
	else if (!ft_strcmp(word_cmd[0], "echo"))
		execute_echo(word_cmd);
	else if (!ft_strcmp(word_cmd[0], "exit"))
		execute_exit(exec_struct, word_cmd);
}

void	handle_builtin_command(t_execution *exec_struct, \
							t_command *command, t_context context, int check)
{
	int	std_out;
	int	std_in;
	int	result;

	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	result = exec_redirection(exec_struct, context);
	if (check)
		select_builtins_command(exec_struct, command);
	if (context.fd[STDOUT_FILENO] != STDOUT_FILENO || \
		context.fd[STDIN_FILENO] != STDIN_FILENO || result)
	{
		dup2(std_out, STDOUT_FILENO);
		dup2(std_in, STDIN_FILENO);
	}
	close(std_out);
	close(std_in);
}
