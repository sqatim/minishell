/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:49:07 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/26 14:44:18 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

unsigned long long ft_atoull(const char *str)
{
	unsigned long long result;
	int counter;
	int i;

	i = 0;
	result = 0;
	counter = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f' ||\
		str[i] == '\n' || str[i] == '\v' || str[i] == '\t')
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
