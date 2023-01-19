/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:06:21 by oussama           #+#    #+#             */
/*   Updated: 2023/01/19 02:06:58 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/minishell.h"

char	*between_quots_h(char *line, int *indice, char type)
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

char	*check_quotes_h(int *indice, char *line)
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
			str = between_quots_h(line, &i, line[i]);
			*indice = i;
			return (str);
		}
	}
	else
		*indice = i;
	return (ft_strdup(""));
}
