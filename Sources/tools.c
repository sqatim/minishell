/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:58:46 by kernel            #+#    #+#             */
/*   Updated: 2023/01/19 01:48:31 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_redirection	*retrieve_redirections(t_command *command)
{
	t_redirection	*head;
	t_redirection	*remember;
	t_command		*tmp;

	head = NULL;
	tmp = command;
	while (tmp)
	{
		if (tmp->redirections)
		{
			remember = tmp->redirections;
			while (remember)
			{
				head = create_redirection_node(head, remember);
				remember = remember->next;
			}
		}
		tmp = tmp->next;
	}
	return (head);
}

void	manage_command(t_execution *exec_struct, char *buffer)
{
	t_redirection	*redirections;
	int				check;

	redirections = retrieve_redirections(exec_struct->command);
	if (redirections)
	{
		handle_redirection(exec_struct->env, \
			redirections, &check);
		free_redirection(redirections);
	}
	start_execution(exec_struct, exec_struct->command);
	free_string(buffer);
	buffer = NULL;
	if (exec_struct->command)
		exec_struct->command = free_command(exec_struct->command);
	if (exec_struct->redirections_sorted)
		exec_struct->redirections_sorted = \
			free_redirection(exec_struct->redirections_sorted);
	return ;
}

void	minishell_loop(t_execution *exec_struct)
{
	char	*buffer;

	signal_handler();
	while (1)
	{
		buffer = readline("minishell:> ");
		if (!buffer)
			ft_exit(exec_struct, 130);
		if (buffer[0] != '\0')
		{
			exec_struct->command = startParse(exec_struct->env, buffer);
			add_history(buffer);
			manage_command(exec_struct, buffer);
		}
		else
			free(buffer);
		g_global.here_doc = 0;
	}
}

char	*ft_get_env(t_env *env, char *key)
{
	t_env	*tmp;
	int		index;
	char	*tmp_key;

	tmp = env;
	tmp_key = ft_strdup(key);
	index = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, tmp_key) && tmp->display)
		{
			while (tmp->content[index] != '=')
				index++;
			free_string(tmp_key);
			return (&tmp->content[++index]);
		}
		tmp = tmp->next;
	}
	free_string(tmp_key);
	return (NULL);
}

char	*ft_get_node_env_without_exception(t_env *env, char *key)
{
	t_env	*tmp;
	int		index;
	char	*tmp_key;

	tmp = env;
	tmp_key = ft_strdup(key);
	index = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, tmp_key))
		{
			while (tmp->content[index] != '=' && tmp->content[index])
				index++;
			free_string(tmp_key);
			return (&tmp->content[index]);
		}
		tmp = tmp->next;
	}
	free_string(tmp_key);
	return (NULL);
}
