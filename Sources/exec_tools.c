/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:17:35 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/19 02:17:29 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_env	*switch_env_node(t_env *first_tmp, t_env **second_tmp)
{
	char	*content;
	char	*value;
	char	*name;
	int		display;

	content = first_tmp->content;
	value = first_tmp->value;
	name = first_tmp->name;
	display = first_tmp->display;
	first_tmp->content = (*second_tmp)->content;
	first_tmp->value = (*second_tmp)->value;
	first_tmp->name = (*second_tmp)->name;
	first_tmp->display = (*second_tmp)->display;
	(*second_tmp)->content = content;
	(*second_tmp)->value = value;
	(*second_tmp)->name = name;
	(*second_tmp)->display = display;
	return (first_tmp);
}

int	exec_input_redirection(t_redirection *input)
{
	int		fd_input;
	char	*path;

	if (!ft_strcmp(input->type, "<<"))
	{
		path = ft_strjoin("/tmp/", input->f_name);
		fd_input = open(path, O_RDONLY, 0777);
		free_string(path);
		path = NULL;
	}
	else
	{
		fd_input = open(input->f_name, O_RDONLY, 0777);
		if (fd_input == -1)
		{
			print_fd_errors(input->f_name);
			if (g_global.fork_flag == 1)
				exit(1);
		}
	}
	dup2(fd_input, STDIN_FILENO);
	close(fd_input);
	return (1);
}

int	exec_output_redirection(t_redirection *output)
{
	int	fd_output;

	if (!ft_strcmp(output->type, ">>"))
		fd_output = open(output->f_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
	else
		fd_output = open(output->f_name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	dup2(fd_output, STDOUT_FILENO);
	close(fd_output);
	return (2);
}

t_env	*env_clone(t_env *env)
{
	t_env	*new_env;
	t_env	*tmp;

	tmp = env;
	new_env = NULL;
	while (tmp)
	{
		new_env = add_env_node(new_env, tmp->content, tmp->display);
		tmp = tmp->next;
	}
	return (new_env);
}
