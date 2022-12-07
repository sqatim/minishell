/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:49:01 by oqatim            #+#    #+#             */
/*   Updated: 2022/12/07 11:23:28 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/minishell.h"

void	add_to_trash(void *ptr, t_trash **stack_trash)
{
	t_trash	*trs;
	t_trash	*node;
	
	trs = (t_trash *)malloc(sizeof(t_trash));
	trs->ptr = ptr;
	trs->next = NULL;
	if (!*stack_trash)
	{
		(*stack_trash) = trs;
		return ;
	}
	node = *stack_trash;
	while (node)
	{
		if (!node->next)
		{
			node->next = trs;
			break ;
		}
		node = node->next;
	}
}

void	*ft_malloc(size_t type, size_t size)
{
	void	*ptr;
	t_trash **stack_trash;

	stack_trash = malloc(sizeof(t_trash));
	ptr = malloc(type * size);
	if (!ptr)
	{
		puts("ra hna salina");
		exit (0);
	}
	add_to_trash(ptr, stack_trash);
	return (ptr);
}
