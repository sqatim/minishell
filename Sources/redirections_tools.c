/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:29:37 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/13 16:47:13 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_redirection	*add_new_redirection(t_redirection *redirections_head, \
		t_redirection *current_redirection)
{
	t_redirection	*tmp;
	t_redirection	*new;

	new = ft_calloc(1, sizeof(t_redirection));
	new->f_name = ft_strdup(current_redirection->f_name);
	new->type = ft_strdup(current_redirection->type);
	new->next = NULL;
	if (!redirections_head)
		return (new);
	tmp = redirections_head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (redirections_head);
}

int	redirections_len(t_redirection *redirection)
{
	t_redirection	*tmp;
	int				index;

	index = 0;
	tmp = redirection;
	while (tmp)
	{
		tmp = tmp->next;
		index++;
	}
	return (index);
}

int	check_redirection(t_redirection *redirection, t_redirection *current)
{
	t_redirection	*tmp;

	tmp = redirection;
	if (!tmp)
		return (1);
	else if ((!ft_strcmp(tmp->type, ">>") || !ft_strcmp(tmp->type, ">")) && \
			(ft_strcmp(current->type, ">>") && ft_strcmp(current->type, ">")))
		return (1);
	else if ((!ft_strcmp(tmp->type, "<") || !ft_strcmp(tmp->type, "<<")) && \
			(ft_strcmp(current->type, "<") && ft_strcmp(current->type, "<<")))
		return (1);
	return (0);
}

t_redirection	*setup_the_last_redirections(t_redirection *current_redirection)
{
	t_redirection	*tmp;
	t_redirection	*new;

	tmp = current_redirection;
	if (!tmp)
		return (NULL);
	new = setup_the_last_redirections(tmp->next);
	if (redirections_len(new) < 2 && check_redirection(new, tmp))
		new = add_new_redirection(new, tmp);
	return (new);
}

t_redirection	*check_type_of_redirection(t_redirection *redirection, int type)
{
	t_redirection	*next;

	if (redirection)
		next = redirection->next;
	if (redirection && type == 0)
	{
		if (!ft_strcmp(redirection->type, "<<") || \
			!ft_strcmp(redirection->type, "<"))
			return (redirection);
		else if (next && (!ft_strcmp(next->type, "<<") || \
			!ft_strcmp(next->type, "<")))
			return (next);
	}
	if (redirection && type == 1)
	{
		if (!ft_strcmp(redirection->type, ">>") || \
			!ft_strcmp(redirection->type, ">"))
			return (redirection);
		else if (next && (!ft_strcmp(next->type, ">>") || \
			!ft_strcmp(next->type, ">")))
			return (next);
	}
	return (NULL);
}
