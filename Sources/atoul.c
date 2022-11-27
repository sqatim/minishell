/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:49:07 by sqatim            #+#    #+#             */
/*   Updated: 2022/11/27 23:09:14 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	check(int counter, int sign, int result)
// {
// 	if (counter > 19)
// 	{
// 		if (sign > 0)
// 			return (-1);
// 		else
// 			return (0);
// 	}
// 	return (result * sign);
// }

unsigned long long	ft_atoull(const char *str)
{
	int	i;
	unsigned long long	result;
	int	counter;

	i = 0;
	result = 0;
	counter = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f' || str[i] == '\n' \
			|| str[i] == '\v' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		counter++;
	}
	return (result);
}
