/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 08:58:45 by oqatim            #+#    #+#             */
/*   Updated: 2022/12/07 11:23:28 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

t_token *creat_first_node(t_token *head)
{
	head = ft_malloc(sizeof(t_token), 1);
	if (!head)
		return (NULL);
	head->value = ft_strdup("RIEN");
	head->next = NULL;
	return (head);
}

char *get_word(char *line, int *index)
{
	char *str;
	int len;
	int i;
	int j;

	i = *index;
	j = 0;
	len = 1;
	while (line[i] != '\0' && (ft_strchr("|> \"<'", line[i])) == NULL)
	{
		len++;
		i++;
	}
	i = *index;
	str = ft_malloc(sizeof(char), (len + 1));
	while (line[i] && (ft_strchr("|> \"<'", line[i])) == NULL)
		str[j++] = line[i++];
	str[j] = '\0';
	*index = i;
	return (str);
}

t_token *get_token_word(t_token *ptr, char *line, int *index, t_main *m_main)
{
	char *token;
	int i;
	int j;
	t_token *tmp;
	int check;

	i = *index;
	token = NULL;
	while (line[i] && line[i] != '\n' && (ft_strchr("|> <", line[i])) == NULL)
	{
		check = 0;
		if (line[i] == '\'' || line[i] == '"')
		{
			j = i;
			token = check_quotes(&i, line, m_main);
			if (j > 0 && line[j - 1] != ' ' && line[j - 1] != '\t')
			{
				tmp = ptr;
				while (tmp->next)
					tmp = tmp->next;
				tmp->value = ft_strjoin_prs(tmp->value, token);
			}
			else
				ptr = add_to_end_lexe(ptr, token);
			*index = i;
			return (ptr);
		}
		else
		{
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
				tmp->value = ft_strjoin_prs(tmp->value, token);
			}
			else
				ptr = add_to_end_lexe(ptr, token);
			*index = i;
			return (ptr);
		}
	}
	// if (token)
	// 	free (token);
	return (ptr);
}

t_token *ft_lexer(t_token *head, t_main *m_main, char *line)
{
	t_token *ptr;
	int i;

	i = 0;
	// head = creat_first_node(head);
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

void test()
{
	system("leaks a.out");
}

int startParse(char **env)
{
	// t_token *head;
	// t_command *cmd;
	t_redirection *redi;
	t_main *m_main;
	
	redi = NULL;
	// head = NULL;
	// m_main->cmd = NULL;
	m_main = ft_malloc(sizeof(t_main), 1);
	m_main->h_env = get_env(env);
	m_main->list = creat_first_node(m_main->list);
	m_main->list = ft_lexer(m_main->list, m_main, " oussama ibra | cat -e | ls -la ");
	ft_check_syntax(m_main->list);
	m_main->cmd = ft_parse(m_main->cmd, m_main->list);
	return (0);
}

// atexit(test);
// system("leaks minishell ");
// int main(int ac, char **av, char **env)
// {
// 	t_main *m_main;

// 	(void)ac;
// 	(void)av;
// 	m_main = NULL;
// 	// while(1)
// 	// {
// 		// m_main->line = readline("minishellll = ");
// 		_main(env, m_main);

// 	// }
// }
