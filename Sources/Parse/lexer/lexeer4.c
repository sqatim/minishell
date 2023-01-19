/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeer4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:00:19 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/19 16:50:31 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

void	ft_free_token(t_token *head)
{
	t_token	*tmp;

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

void	ft_free(t_main *m_main)
{
	ft_free_token(m_main->list);
	free(m_main);
	m_main = NULL;
}

int	quotes_checker(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			i = find_quotes(line, &i, line[i]);
			if (i == 0)
			{
				printf("syntax error : enter more quots \n");
				g_global.exit = 258;
				return (0);
			}
		}
		i++;
	}
	return (1);
}
