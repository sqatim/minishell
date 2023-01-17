/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utilis3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:59:28 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/17 14:52:28 by samirqatim       ###   ########.fr       */
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
	int x;
	char *dup;

	x = 0;
	index = *i;
	while ((*token)[index] == '$')
	{
		index++;
		x++;
	}
	// if ((*token)[index] == '?')
	// {
	// 	exit = ft_itoa(G_GLOBAL);
	// 	str = ft_strjoin_prs(exit, &(*token)[++index]);
	// 	return (str);
	// }
	if ((*token)[index] == '\0' && x != 1)
	{
		if (x % 2 != 0)
		{
			str = ft_strdup("$");
			return (str);
		}
		else
			return (NULL);
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
