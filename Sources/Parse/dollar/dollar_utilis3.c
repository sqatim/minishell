/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utilis3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:59:28 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/09 13:20:12 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

char *last_part(char **token, int *index)
{
	char *str;
	int len;
	int i;
	int j;

	i = *index;
	len = 0;
	j = 0;
	while ((*token)[i++])
		len++;
	str = malloc(sizeof(char) * (len + 1));
	i = *index;
	while ((*token)[i])
		str[j++] = (*token)[i++];
	str[j] = '\0';
	return (str);
}

char *take_last_part(char **token, int *i)
{
	char *str;
	int index;
	char *exit;

	index = *i;
	while ((*token)[index] == '$')
		index++;
	if ((*token)[index] == '?')
	{
		exit = ft_itoa(g_global.exit);
		str = ft_strjoin(exit, &(*token)[++index]);
		return (str);
	}
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

char *take_last_token(char **token)
{
	char *str;
	int index;

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
