/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeer3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:15:28 by oussama           #+#    #+#             */
/*   Updated: 2023/01/16 13:55:24 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

t_token *ft_norm_word(t_token *ptr, t_main *m_main, int *index, char *line)
{
	int i;
	char *token;
	t_token *tmp;
	int check;

	i = *index;
	check = 0;
	if (i > 0 && (line[i - 1] == '\'' || line[i - 1] == '"'))
		check = 1;
	token = get_word(line, &i);
	while (search_dollar(token) == 1)
		expand_after_dollar(&token, m_main);
	if (check == 1)
	{
		tmp = ptr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->value = ft_strjoin(tmp->value, token);
	}
	else
		ptr = add_to_end_lexe(ptr, token);
	*index = i;
	// if (token)
	// 	free(token);
	return (ptr);
}

t_token *ft_norm_quots(t_token *ptr, t_main *m_main, int *index, char *line)
{
	int j;
	int i;
	char *token;
	t_token *tmp;

	i = *index;
	j = i;
	token = check_quotes(&i, line, m_main);
	if (j > 0 && line[j - 1] != ' ' && line[j - 1] != '\t')
	{
		tmp = ptr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->value = ft_strjoin(tmp->value, token);
	}
	else
		ptr = add_to_end_lexe(ptr, token);
	*index = i;
	return (ptr);
}

t_token *ft_norm_word_h(t_token *ptr, t_main *m_main, int *index, char *line)
{
	int i;
	char *token;
	t_token *tmp;
	int check;

	i = *index;
	check = 0;
	if (i > 0 && (line[i - 1] == '\'' || line[i - 1] == '"'))
		check = 1;
	token = get_word(line, &i);
	if (check == 1)
	{
		tmp = ptr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->value = ft_strjoin(tmp->value, token);
	}
	else
		ptr = add_to_end_lexe(ptr, token);
	*index = i;
	// if (token)
	// 	free(token);
	return (ptr);
}

t_token *ft_norm_quots_h(t_token *ptr, t_main *m_main, int *index, char *line)
{
	int j;
	int i;
	char *token;
	t_token *tmp;

	i = *index;
	j = i;
	token = check_quotes_h(&i, line, m_main);
	if (j > 0 && line[j - 1] != ' ' && line[j - 1] != '\t')
	{
		tmp = ptr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->value = ft_strjoin(tmp->value, token);
	}
	else
		ptr = add_to_end_lexe(ptr, token);
	*index = i;
	return (ptr);
}

t_token *ft_check_norm(t_token *ptr, t_main *m_main, int *index, char *line)
{
	int i;

	i = *index;
	if (line[i] == '\'' || line[i] == '"')
	{
		ptr = ft_norm_quots_h(ptr, m_main, &(i), line);
		*index = i;
		return (ptr);
	}
	else
	{
		ptr = ft_norm_word_h(ptr, m_main, &(i), line);
		*index = i;
		return (ptr);
	}
}