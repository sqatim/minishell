/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeer4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:00:19 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/18 13:03:03 by oqatim           ###   ########.fr       */
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
