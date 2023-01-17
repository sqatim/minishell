/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:06:21 by oussama           #+#    #+#             */
/*   Updated: 2023/01/13 11:23:15 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*between_quots_h(char *line, int *indice, char type, t_main *main)
{
	char	*token;
	int		i;
	int		j;
	int		x;

	j = 0;
	i = *indice;
	x = i;
	while (line[++x] != type)
		j++;
	token = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (line[++i] != type)
		token[j++] = line[i];
	i++;
	token[j] = '\0';
	*indice = i;
	return (token);
}

char	*check_quotes_h(int *indice, char *line, t_main *m_main)
{
	char	*str;
	int		i;

	i = *indice;
	if (find_quotes(line, &i, line[i]))
	{
		if (quotes_after_quotes(line, &i, line[i]))
		{
			i -= 2;
			str = quotes_after_quotes(line, &i, line[i]);
			*indice = i;
			return (str);
		}
		else
		{
			str = between_quots_h(line, &i, line[i], m_main);
			*indice = i;
			return (str);
		}
	}
	else
		*indice = i;
	return (ft_strdup(""));
}
