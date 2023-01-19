/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 08:58:45 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/19 02:08:55 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

t_token	*creat_first_node(t_token *head)
{
	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	head->value = ft_strdup("RIEN");
	head->next = NULL;
	return (head);
}

char	*get_word(char *line, int *index)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = *index;
	j = 0;
	len = 1;
	while (line[i] != '\0' && (ft_strchr("|> \"<'", line[i])) == NULL)
	{
		len++;
		i++;
	}
	i = *index;
	str = malloc(sizeof(char) * (len + 1));
	while (line[i] && (ft_strchr("|> \"<'", line[i])) == NULL)
		str[j++] = line[i++];
	str[j] = '\0';
	*index = i;
	return (str);
}

t_token	*get_token_word(t_token *ptr, char *line, int *i, t_main *m_main)
{
	if (ft_strcmp(ptr->value, "<<") == 0)
	{
		while (line[*i] && line[*i] != '\n'
			&& (ft_strchr("|> <", line[*i])) == NULL)
		{
			ptr = ft_check_norm(ptr, &(*i), line);
			return (ptr);
		}
	}
	else
	{
		while (line[*i] && line[*i] != '\n'
			&& (ft_strchr("|> <", line[*i])) == NULL)
		{
			if (line[*i] == '\'' || line[*i] == '"')
				ptr = ft_norm_quots(ptr, m_main, &(*i), line);
			else
				ptr = ft_norm_word(ptr, m_main, &(*i), line);
			return (ptr);
		}
	}
	return (ptr);
}

t_token	*ft_lexer(t_token *head, t_main *m_main, char *line)
{
	t_token	*ptr;
	int		i;

	i = 0;
	head = creat_first_node(head);
	ptr = head;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i])
	{
		while (line[i])
		{
			if (i == 0)
				while (line[i] == ' ' || line[i] == '\t')
					i++;
			if (line[i] == '|' || line[i] == '>' || line[i] == '<')
				ptr = get_different_token(ptr, line, &i);
			if (line[i] && (ft_strchr("|> <", line[i])) == NULL)
				ptr = get_token_word(ptr, line, &i, m_main);
			else
				i++;
		}
	}
	return (head);
}

t_command	*start_parse(t_env *env, char *buffer)
{
	t_command	*cmd;
	t_main		*m_main;

	cmd = NULL;
	m_main = malloc(sizeof(t_main));
	m_main->h_env = env;
	m_main->list = ft_lexer(m_main->list, m_main, buffer);
	if (ft_check_syntax(m_main))
		return (NULL);
	if (m_main->list)
	{
		m_main->cmd = ft_parse(m_main->list);
		cmd = m_main->cmd;
		ft_free(m_main);
	}
	return (cmd);
}
