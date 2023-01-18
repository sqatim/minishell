/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:48:42 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/18 12:57:30 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	check_error_in_unset(char *argument, int *status)
{
	if (!argument[0] || ft_isdigit(argument[0]))
	{
		print_unset_error(argument, status);
		return (0);
	}
	else
		return (1);
}

void	check_status_in_unset(int status)
{
	if (status)
		g_global.exit = 0;
	else
		g_global.exit = 1;
}

t_env	*execute_unset_for_export(t_execution *exec_struct, t_env *env, \
					char *argument)
{
	t_env	*tmp;
	char	*tmp_argument;

	if (argument)
	{
		tmp_argument = ft_strdup(argument);
		tmp = env;
		if (!unset_itterator(&tmp, tmp_argument))
			env = NULL;
		if (tmp && !tmp->prev)
			env = tmp;
		free(tmp_argument);
		tmp_argument = NULL;
	}
	g_global.exit = 0;
	exec_struct->envArray = convert_env_to_array(exec_struct, env);
	return (env);
}

t_env	*execute_unset(t_execution *exec_struct, t_env *env, char **argument)
{
	t_env	*tmp;
	char	*tmp_argument;
	int		index;
	int		status;

	index = 1;
	status = 1;
	while (argument[index])
	{
		if (check_error_in_unset(argument[index], &status))
		{
			tmp_argument = ft_strdup(argument[index]);
			tmp = env;
			if (!unset_itterator(&tmp, tmp_argument))
				env = NULL;
			if (tmp && !tmp->prev)
				env = tmp;
			free(tmp_argument);
			tmp_argument = NULL;
		}
		index++;
	}
	check_status_in_unset(status);
	exec_struct->envArray = convert_env_to_array(exec_struct, env);
	return (env);
}
