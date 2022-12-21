/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:17:26 by oussama           #+#    #+#             */
/*   Updated: 2022/12/21 22:14:44 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/minishell.h"

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
		puts("error 404");
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
		puts("error 403");
		i = 1;
	}
	if (!ft_strcmp(head->value, RIEN) && head->next
		&& (!ft_strcmp(head->next->value, PIPE)
			|| !ft_strcmp(head->next->value, NWLN)))
	{
		puts("error 402");
		i = 1;
	}
	if (ft_norm_redi(head->value))
		i = ft_error_redi(head);
	return (i);
}

void	ft_check_syntax(t_token *head)
{
	while (head != NULL)
	{	
		if (ft_check(head))
			exit(0);
		head = head->next;
	}
}
