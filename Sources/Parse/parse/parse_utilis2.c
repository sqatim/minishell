/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilis2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 04:45:41 by oqatim            #+#    #+#             */
/*   Updated: 2022/11/22 05:14:00 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_norm_redi(char *value)
{
	if (!ft_strcmp(value, REDI_LIM) || !ft_strcmp(value, REDI_LIS)
		|| !ft_strcmp(value, HERDOC) || !ft_strcmp(value, DOUBLE_LIS))
		return (1);
	return (0);
}

int	ft_check_word(char *token)
{
	if (ft_strcmp(token, PIPE) && ft_strcmp(token, NWLN)
		&& ft_strcmp(token, RIEN) && ft_strcmp(token, REDI_LIM)
		&& ft_strcmp(token, HERDOC) && ft_strcmp(token, REDI_LIS)
		&& ft_strcmp(token, DOUBLE_LIS))
		return (1);
	return (0);
}
