/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 00:05:30 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/16 13:56:15 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	t;

	i = 0;
	t = 0;
	if (!src)
		return (0);
	while (i + 1 < size && src[i])
	{
		dst[t++] = src[i++];
	}
	if (t < size)
		dst[t] = '\0';
	while (src[i])
		i++;
	return (i);
}
