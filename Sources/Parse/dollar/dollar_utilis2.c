/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utilis2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:03:35 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/17 14:38:43 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

void take_after_dollar(char **token, int *index, char **name)
{
	int i;
	int j;

	i = *index;
	j = 0;
	if ((*token)[i] == '$' && (*token)[i + 1] == '\0')
		(*name)[j++] = (*token)[i++];
	else
	{
		while ((*token)[i] == '$')
			i++;
		while (alpha_numeric((*token)[i]))
		{
			(*name)[j] = (*token)[i];
			i++;
			j++;
		}
	}
	(*name)[j] = '\0';
	*index = i;
}

void ft_check_dollar(char **token, int *index, t_main *m_main)
{
	int count;
	int i;

	i = *index;
	count = 0;
	while ((*token)[i++] == '$')
		count++;
	if (count % 2 == 0)
		m_main->flag_dollar = 0;
	else
		m_main->flag_dollar = 1;
}

int len_dollar_name(char **token)
{
	int flag;
	int len;
	int i;

	len = 0;
	i = 0;
	flag = 0;
	if ((*token)[i] == '$')
	{
		if ((*token)[i + 1] == '\0')
			len++;
	}
	while ((*token)[i] != '\0' && flag == 0)
	{
		if ((*token)[i] == '$')
		{
			while ((*token)[i] == '$')
				i++;
			while (alpha_numeric((*token)[i++]) == 1)
				len++;
			flag = 1;
		}
		i++;
	}
	return (len);
}

int alpha_numeric(char c)
{
	if (!c)
		return (0);
	if ((c >= 0 && c <= 9) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}
