/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utilis3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:59:28 by oqatim            #+#    #+#             */
/*   Updated: 2022/12/21 22:12:31 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

char	*last_part(char **token, int *index)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = *index;
	len = 0;
	j = 0;
	while ((*token)[i++])
		len++;
	str = ft_malloc(sizeof(char), len + 1);
	i = *index;
	while ((*token)[i])
		str[j++] = (*token)[i++];
	str[j] = '\0';
	return (str);
}

char	*take_last_part(char **token, int *i)
{
	char	*str;
	int		index;

	index = *i;
	while ((*token)[index] == '$')
		index++;
	while ((*token)[index] != '\0')
	{
		if (!alpha_numeric((*token)[index]))
		{
			str = last_part(token, &index);
			return (str);
		}
		index++;
	}
	return (NULL);
}

char	*take_last_token(char **token)
{
	char	*str;
	int		index;

	index = 0;
	while ((*token)[index])
	{
		if ((*token)[index] == '$')
		{
			str = take_last_part(token, &index);
			return (str);
		}
		index++;
	}
	return (NULL);
}
