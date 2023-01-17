/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:23:48 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/17 18:49:58 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	iterate_and_sort_env(t_env **first_tmp)
{
	t_env	*second_tmp;

	second_tmp = (*first_tmp)->next;
	while (second_tmp)
	{
		if (ft_strcmp(second_tmp->content, (*first_tmp)->content) < 0)
			*first_tmp = switch_env_node(*first_tmp, &second_tmp);
		second_tmp = second_tmp->next;
	}
	*first_tmp = (*first_tmp)->next;
}

int	check_exit_argument_type(char *argument)
{
	int	index;
	int	type;
	int	len;

	len = 0;
	index = 0;
	type = 1;
	if (argument[index] == '-' || argument[index] == '+')
	{
		if (argument[index == '-'])
			type = -1;
		index++;
		if (!argument[index])
			return (0);
	}
	while (argument[index])
	{
		if (!ft_isdigit(argument[index]))
			return (0);
		index++;
		len++;
	}
	if (len > 19)
		return (0);
	return (type);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if ((!s1 || !s2))
		return (-1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (((s1[i] == '\0' && s2[i] != '\0') || (s2[i] == '\0' && s1[i] != '\0')))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

t_env	*sort_env(t_env *env)
{
	t_env	*first_tmp;
	t_env	*env_export;

	env_export = env_clone(env);
	if (env_export)
	{
		first_tmp = env_export;
		while (first_tmp->next)
			iterate_and_sort_env(&first_tmp);
	}
	return (env_export);
}
