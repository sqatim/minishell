/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 08:59:56 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/19 16:52:28 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/minishell.h"

char	*quotes_after_quotes(char *line, int *indice, char type)
{
	int		i;
	char	*str;

	i = *indice;
	if ((line[i] == '"' && line[i + 1] == type)
		|| (line[i] == '\'' && line[i + 1] == type))
	{
		str = ft_strdup("");
		*indice += 2;
		return (str);
	}
	return (NULL);
}

int	find_quotes(char *line, int *indice, char type)
{
	int	i;

	i = *indice + 1;
	while (line[i])
	{
		if (line[i] == type)
			return (i);
		i++;
	}
	*indice = i;
	return (0);
}

int	word_len_quotes(int i, char *line, char type)
{
	int	j;

	j = 0;
	while (line[++i] != type)
		j++;
	return (j);
}

char	*between_quots(char *line, int *indice, char type, t_main *main)
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
	if (type == '"')
		while (search_dollar(token) == 1)
			expand_after_dollar(&token, main);
	*indice = i;
	return (token);
}

char	*check_quotes(int *indice, char *line, t_main *m_main)
{
	char	*str;
	int		i;

	i = *indice;
	if (find_quotes(line, &i, line[i]))
	{
		str = quotes_after_quotes(line, &i, line[i]);
		if (str)
		{
			*indice = i;
			return (str);
		}
		else
		{
			str = between_quots(line, &i, line[i], m_main);
			*indice = i;
			return (str);
		}
	}
	else
		*indice = i;
	return (ft_strdup(""));
}
