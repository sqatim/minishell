/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:26:11 by oqatim            #+#    #+#             */
/*   Updated: 2022/12/07 11:23:28 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/minishell.h"

t_env *add_to_end_env(t_env *ptr, char *name, char *value)
{
	t_env *tmp;

	tmp = ft_malloc(sizeof(t_env), 1);
	if (!tmp)
		return (NULL);
	tmp->name = name;
	tmp->value = value;
	tmp->next = NULL;
	ptr->next = tmp;
	return (tmp);
}

t_env *creat_first_node_env(t_env *head, char *name, char *value)
{
	head = ft_malloc(sizeof(t_env), 1);
	if (!head)
		return (NULL);
	head->name = name;
	head->value = value;
	head->next = NULL;
	return (head);
}

t_env *get_env(char **env)
{
	t_env *ptr;
	t_env *head;
	char **str;
	int i;

	head = NULL;
	i = 1;
	if (env[0])
	{
		str = ft_split(env[0], '=');
		head = creat_first_node_env(head, str[0], str[1]);
		ptr = head;
		// free(str);
		while (env[i])
		{
			str = ft_split(env[i], '=');
			ptr = add_to_end_env(ptr, str[0], str[1]);
			i++;
			// free(str);
		}
	}
	return (head);
}
