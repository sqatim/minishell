/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utilis3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:59:28 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/19 01:04:48 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;
	int		r;

	i = 0;
	r = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	len = get_lenght(s1, '\0') + get_lenght(s2, '\0') + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1[i])
		str[r++] = s1[i++];
	i = 0;
	while (s2[i])
		str[r++] = s2[i++];
	str[r] = 0;
	free(s1);
	return (str);
}

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
	str = malloc(sizeof(char) * (len + 1));
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
	int		x;

	x = 0;
	index = *i;
	x = boucle_for_dollar(token, &index, x);
	if ((*token)[index] == '?')
		return (ft_global_exit(token, &index));
	if ((*token)[index] == '\0' && x != 1)
		return (ft_len_dollar(x));
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
