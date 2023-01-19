/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utilis4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:03:22 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/19 01:16:48 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

char	*ft_global_exit(char **token, int *index)
{
	char	*exit;
	char	*str;
	int		x;

	x = *index;
	exit = ft_itoa(g_global.exit);
	str = ft_strjoin_free(exit, &(*token)[++x]);
	*index = x;
	return (str);
}

int	boucle_for_dollar(char **token, int *index, int x)
{
	int	i;

	i = *index;
	while ((*token)[i] == '$')
	{
		i++;
		x++;
	}
	*index = i;
	return (x);
}

char	*ft_len_dollar(int x)
{
	char	*str;

	if (x % 2 != 0)
	{
		str = ft_strdup("$");
		return (str);
	}
	else
		return (NULL);
}
