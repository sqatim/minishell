/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:45:02 by oqatim            #+#    #+#             */
/*   Updated: 2022/12/21 22:13:24 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

t_token	*add_to_end_lexe(t_token *head, char *token)
{
	t_token	*tmp;

	tmp = ft_malloc(sizeof(t_token), 1);
	if (!tmp)
		return (NULL);
	tmp->value = token;
	tmp->next = NULL;
	head->next = tmp;
	// if (token)
			// free(token);
	return (tmp);
}

t_token	*add_pipe_node(t_token *ptr, char *line, int i)
{
	char	*token;

	if (line[i] == '|')
	{
		token = ft_strdup("|");
		ptr = add_to_end_lexe(ptr, token);
	}
	return (ptr);
}

t_token	*add_lim_rederi_node(t_token *ptr, char *line, int *index)
{
	char	*token;
	int		i;

	i = *index;
	if (line[i + 1] == '<')
	{
		token = ft_strdup("<<");
		ptr = add_to_end_lexe(ptr, token);
		i++;
		*index = i;
	}
	else
	{
		token = ft_strdup("<");
		ptr = add_to_end_lexe(ptr, token);
	}
	return (ptr);
}

t_token	*add_lis_rederi_node(t_token *ptr, char *line, int *index)
{
	char	*token;
	int		i;

	i = *index;
	if (line[i + 1] == '>')
	{
		token = ft_strdup(">>");
		ptr = add_to_end_lexe(ptr, token);
		i++;
		*index = i;
	}
	else
	{
		token = ft_strdup(">");
		ptr = add_to_end_lexe(ptr, token);
	}
	return (ptr);
}

t_token	*get_different_token(t_token *ptr, char *line, int *index)
{
	int	i;

	i = *index;
	if (line[i] == '|')
		ptr = add_pipe_node(ptr, line, i);
	if (line[i] == '>')
	{
		ptr = add_lis_rederi_node(ptr, line, &i);
		*index = i;
	}
	if (line[i] == '<')
	{
		ptr = add_lim_rederi_node(ptr, line, &i);
		*index = i;
	}
	return (ptr);
}
