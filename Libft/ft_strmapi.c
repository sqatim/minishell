/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:46:59 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/16 13:55:46 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*ss;

	index = 0;
	if (!s || !f)
		return (NULL);
	ss = (char *)malloc(ft_strlen((char *)s) + 1);
	if (!ss)
		return (NULL);
	while (s[index])
	{
		ss[index] = (*f)(index, s[index]);
		index++;
	}
	ss[index] = '\0';
	return (ss);
}
