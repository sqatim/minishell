/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:51:46 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/19 01:52:19 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_command	*free_command(t_command *command)
{
	if (!command)
		return (NULL);
	free_command(command->next);
	free_array_two_dimension(command->command);
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
