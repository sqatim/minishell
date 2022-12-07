/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lltoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:16:38 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/07 11:24:19 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	countnbr(long long n)
{
	int	index;

	index = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		index++;
	}
	return (index);
}

char	*ft_itoapos(long long n)
{
	char	*p;
	int		a;

	if (n >= 0)
	{
		a = countnbr(n);
		p = malloc(sizeof(char) * (a + 1));
		if (!p)
			return (NULL);
		p[a] = '\0';
		a--;
		while (a >= 0)
		{
			p[a] = n % 10 + '0';
			n = n / 10;
			a--;
		}
		return (p);
	}
	return (NULL);
}

char	*ft_lltoa(long long n)
{
	char	*p;
	int		a;

	if (n >= 0)
		return (p = ft_itoapos(n));
	if (n < 0)
	{
		a = countnbr(n);
		p = malloc(sizeof(char) * (a + 2));
		if (!p)
			return (NULL);
		p[a + 1] = '\0';
		p[0] = '-';
		while (a > 0)
		{
			p[a] = (n % 10) * -1 + '0';
			n = n / 10;
			a--;
		}
		return (p);
	}
	return (NULL);
}
