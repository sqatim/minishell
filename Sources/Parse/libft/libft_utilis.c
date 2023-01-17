/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:11:17 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/17 08:54:38 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *str)
{
	char	*ptr;
	int		len;
	int		i;

	i = -1;
	len = get_lenght(str, '\0');
	ptr = malloc(sizeof(char) * (len + 1));
	while (str[++i] != '\0')
		ptr[i] = str[i];
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strcmp(char *str, char *ptr)
{
	int	i;

	i = 0;
	while (str[i] && ptr[i] && str[i] == ptr[i])
		i++;
	return (str[i] - ptr[i]);
}

char	*ft_strchr(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = get_lenght(str, '\0');
	if (c == '\0')
		return (&str[len]);
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}


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


char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	if ((!s) || (unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (ft_strdup(""));
	while (i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}


char	*ft_strjoin(char *s1, char *s2)
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
	free(s2);
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
