/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:16:29 by kernel            #+#    #+#             */
/*   Updated: 2023/01/19 01:04:29 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_env	*assign_env_node(t_env *node, char *key, char *value, char *key_value)
{
	node->name = ft_strdup(key);
	node->value = ft_strdup(value);
	node->content = ft_strdup(key_value);
	return (node);
}

t_env	*setup_env(char **envp)
{
	int		index;
	t_env	*env;

	env = NULL;
	index = 0;
	while (envp[index])
	{
		env = add_env_node(env, envp[index], 1);
		index++;
	}
	return (env);
}

t_env	*init_env(t_env *new, char *content, int display)
{
	int	index;

	index = 0;
	if (display == 0)
	{
		new->name = ft_strdup(content);
		new->value = NULL;
	}
	else
	{
		while (content[index] != '=')
			index++;
		new->name = ft_substr(content, 0, index);
		new->value = ft_substr(content, ++index, ft_strlen(content));
	}
	new->content = ft_strdup(content);
	new->display = display;
	return (new);
}

t_env	*add_env_node(t_env *head, char *content, int display)
{
	t_env	*tmp;
	t_env	*new;

	new = (t_env *)calloc(1, sizeof(t_env));
	if (!new)
		exit(1);
	new = init_env(new, content, display);
	new->next = NULL;
	new->prev = NULL;
	if (!head)
		return (new);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (head);
}

t_export	export_init(void)
{
	t_export	export;

	export.status = 1;
	export.index = 1;
	export.key_value = NULL;
	export.key_value_joined = NULL;
	export.old_value = NULL;
	return (export);
}
