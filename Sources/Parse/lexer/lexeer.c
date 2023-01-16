/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 08:58:45 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/16 18:40:08 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

t_token *creat_first_node(t_token *head)
{
	head = malloc(sizeof(t_token));
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
	str = malloc(sizeof(char) * (len + 1));
	while (line[i] && (ft_strchr("|> \"<'", line[i])) == NULL)
		str[j++] = line[i++];
	str[j] = '\0';
	*index = i;
	return (str);
}

t_token *get_token_word(t_token *ptr, char *line, int *i, t_main *m_main)
{
	if (ft_strcmp(ptr->value, "<<") == 0)
	{
		while (line[*i] && line[*i] != '\n' && (ft_strchr("|> <", line[*i])) == NULL)
		{
			ptr = ft_check_norm(ptr, m_main, &(*i), line);
			return (ptr);
		}
	}
	else
	{
		while (line[*i] && line[*i] != '\n' && (ft_strchr("|> <", line[*i])) == NULL)
		{
			if (line[*i] == '\'' || line[*i] == '"')
			{
				ptr = ft_norm_quots(ptr, m_main, &(*i), line);
				return (ptr);
			}
			else
			{
				ptr = ft_norm_word(ptr, m_main, &(*i), line);
				return (ptr);
			}
		}
	}
	return (ptr);
}

t_token *ft_lexer(t_token *head, t_main *m_main, char *line)
{
	t_token *ptr;
	int i;

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

void print(t_command *cmd)
{
	t_command *tmp = cmd;
	printf("**********************\n");
	while (cmd != NULL)
	{
		printf("----------------command-------------\n");
		int index = 0;
		while (cmd->command[index] != NULL)
		{
			printf("%s\n", cmd->command[index++]);
		}
		printf("----------------redirection-------------\n");

		while (cmd->redirections)
		{
			printf("type de redi ===> |%s| file name =====> |%s|\n", cmd->redirections->type, cmd->redirections->f_name);
			cmd->redirections = cmd->redirections->next;
		}
		cmd = cmd->next;
	}
	printf("**********************\n");
	cmd = tmp;
}

void ft_free_token(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
	if (head == NULL)
	{
		free(head);
		head = NULL;
	}
}

void ft_free(t_main *m_main)
{
	ft_free_token(m_main->list);
	if (m_main->line)
		free(m_main->line);
	free(m_main);
	m_main = NULL;
}

t_command *startParse(t_env *env, char *buffer)
{
	// t_token *head;
	t_command *cmd;
	// t_redirection *redi;
	t_main *m_main;
	// redi = NULL;
	// head = NULL;
	// m_main->cmd = NULL;
	m_main = malloc(sizeof(t_main));
	m_main->h_env = env;
	// m_main->list = creat_first_node(m_main->list);
	// m_main->list = ft_lexer(m_main->list, m_main, "$HOME | $HOME");
	// m_main->list = ft_lexer(m_main->list, m_main, " \"$??HOME?????\"");
	// m_main->list = ft_lexer(m_main->list, m_main, " \"$??HOME?????\" >> out | $HOME");
	// m_main->list = ft_lexer(m_main->list, m_main, "\"samir\" \"oussama\"");
	// m_main->list = ft_lexer(m_main->list, m_main, "e\"c\"h\"o\"");
	// m_main->list = ft_lexer(m_main->list, m_main, "ls | ls | ls| ls > file | export");
	m_main->list = ft_lexer(m_main->list, m_main, buffer);
	// m_main->list = ft_lexer(m_main->list, m_main, "ls | export");
	// m_main->list = ft_lexer(m_main->list, m_main, "<in \"echo\" \"$HOME\" >> out | ls -la >> 'out'");
	ft_check_syntax(m_main->list);
	m_main->cmd = ft_parse(m_main->list);
	// print(m_main->cmd);
	cmd = m_main->cmd;
	ft_free(m_main);
	return (cmd);
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
