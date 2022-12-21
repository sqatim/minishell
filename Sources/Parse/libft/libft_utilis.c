/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:11:17 by oqatim            #+#    #+#             */
/*   Updated: 2022/12/21 22:16:24 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"


int	get_lenght(char *ln, char c)
{
	int	i;

	i = 0;
	if (ln == NULL)
		return (0);
	while (ln[i] && ln[i] != c)
		i++;
	return (i);
}


char	*ft_strjoin_prs(char *s1, char *s2)
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
	str = ft_malloc(sizeof(char), len + 1);
	if (!str)
		return (NULL);
	while (s1[i])
		str[r++] = s1[i++];
	i = 0;
	while (s2[i])
		str[r++] = s2[i++];
	str[r] = 0;
	// free(s1);
	return (str);
}

// int	ft_strcmp(char *str, char *ptr)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && ptr[i] && str[i] == ptr[i])
// 		i++;
// 	return (str[i] - ptr[i]);
// }
