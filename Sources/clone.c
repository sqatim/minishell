/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:31:18 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/18 20:13:13 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	**clone_command_words(char **str)
{
	int		index;
	char	**new;

	index = 0;
	while (str[index])
		index++;
	new = ft_calloc(++index, sizeof(char *));
	index = 0;
	while (str[index])
	{
		new[index] = ft_strdup(str[index]);
		index++;
	}
	return (new);
}

t_redirection	*create_redirection_node(t_redirection *head, \
			t_redirection *source)
{
	t_redirection	*tmp;
	t_redirection	*new;

	tmp = head;
	new = ft_calloc(1, sizeof(t_redirection));
	new->next = NULL;
	new->type = ft_strdup(source->type);
	new->f_name = ft_strdup(source->f_name);
	if (!head)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}

t_redirection	*clone_command_redirections(t_redirection *source)
{
	t_redirection	*new;
	t_redirection	*tmp;

	tmp = source;
	new = NULL;
	while (tmp)
	{
		new = create_redirection_node(new, tmp);
		tmp = tmp->next;
	}
	return (new);
}

t_command	*clone_node(t_command *source)
{
	t_command	*new;

	new = ft_calloc(1, sizeof(t_command));
	new->command = clone_command_words(source->command);
	new->redirections = clone_command_redirections(source->redirections);
	return (new);
}
