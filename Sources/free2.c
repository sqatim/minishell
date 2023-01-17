/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:51:46 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/17 19:32:56 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	unlink_heredocument_files(t_redirection *redirections)
{
	t_redirection	*tmp;
	char			*path;

	tmp = redirections;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "<<"))
		{
			path = ft_strjoin("/tmp/", tmp->f_name);
			unlink(path);
			free(path);
		}
		tmp = tmp->next;
	}
}

t_command	*free_command(t_command *command)
{
	if (!command)
		return (NULL);
	free_command(command->next);
	free_array_two_dimension(command->command);
	unlink_heredocument_files(command->redirections);
	free_redirection(command->redirections);
	free(command);
	command = NULL;
	return (NULL);
}

void	free_export_struct(t_export *export)
{
	if (export->key_value)
	{
		free_array_two_dimension(export->key_value);
		export->key_value = NULL;
	}
	if (export->key_value_joined)
	{
		free(export->key_value_joined);
		export->key_value_joined = NULL;
	}
	if (export->old_value)
	{
		free(export->old_value);
		export->old_value = NULL;
	}
}

void	free_env_node_content(t_env *node)
{
	if (node->content)
	{
		free(node->content);
		node->content = NULL;
	}
	if (node->name)
	{
		free(node->name);
		node->name = NULL;
	}
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
}

void	free_here_document_redirection(char **buffer, char **path, \
			char **delimiter, int fd)
{
	free(*delimiter);
	free(*path);
	free(*buffer);
	*buffer = NULL;
	*path = NULL;
	*delimiter = NULL;
	close(fd);
}
