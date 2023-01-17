/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:17:26 by oussama           #+#    #+#             */
/*   Updated: 2023/01/17 14:18:10 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_redi(t_token *head)
{
	int		i;

	i = 0;
	if (!head->next || !ft_strcmp(head->next->value, PIPE)
		|| !ft_strcmp(head->next->value, NWLN)
		|| !ft_strcmp(head->next->value, RIEN)
		|| !ft_strcmp(head->next->value, REDI_LIM)
		|| !ft_strcmp(head->next->value, HERDOC)
		|| !ft_strcmp(head->next->value, REDI_LIS)
		|| !ft_strcmp(head->next->value, DOUBLE_LIS))
	{
		printf("syntax error near unexpected token redirection\n");
		i = 1;
	}
	return (i);
}

int	ft_check(t_token *head)
{
	int	i;

	i = 0;
	if (!ft_strcmp(head->value, PIPE) && (!head->next
			|| (!ft_strcmp(head->next->value, PIPE)
				|| !ft_strcmp(head->next->value, NWLN))))
	{
		printf("syntax error near unexpected token \"|\" \n");
		i = 1;
	}
	if (!ft_strcmp(head->value, RIEN) && head->next
		&& (!ft_strcmp(head->next->value, PIPE)
			|| !ft_strcmp(head->next->value, NWLN)))
	{
		printf("syntax error near unexpected token \"|\" \n");
		i = 1;
	}
	if (ft_norm_redi(head->value))
		i = ft_error_redi(head);
	return (i);
}

int	ft_check_syntax(t_main *m_main)
{
	t_token *head;

	head = m_main->list;	
	while (head != NULL)
	{	
		if (ft_check(head))
		{
			ft_free(m_main);
			return (1);
		}
		head = head->next;
	}
	return (1);
}
