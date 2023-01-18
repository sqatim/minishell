/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:46:09 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/18 12:37:37 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	print_fd_errors(char *file_name)
{
	ft_putstr_fd(file_name, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	print_value_of_export(char *value)
{
	int	index;

	index = 0;
	while (value[index])
	{
		if (value[index] == '"')
			ft_putchar_fd('\\', 1);
		ft_putchar_fd(value[index], 1);
		index++;
	}
}

void	print_env_with_export_second(t_env *sorted_env, int index, int display)
{
	char	*key;
	char	*value;

	if (sorted_env->content[index] == '=')
		++index;
	key = ft_substr(sorted_env->content, 0, index);
	ft_putstr_fd("declare -x ", 1);
	if (display == 0)
		ft_putendl_fd(key, 1);
	else if (display == 1)
	{
		ft_putstr_fd(key, 1);
		value = ft_substr(sorted_env->content, index, \
							ft_strlen(sorted_env->content));
		ft_putstr_fd("\"", 1);
		print_value_of_export(value);
		ft_putendl_fd("\"", 1);
		free(value);
	}
	free(key);
}

void	print_env_with_export(t_env *env)
{
	t_env	*sorted_env;
	t_env	*tmp;
	int		index;

	sorted_env = sort_env(env);
	tmp = sorted_env;
	while (tmp)
	{
		index = 0;
		while (tmp->content[index] != '=' && tmp->content[index])
			index++;
		print_env_with_export_second(tmp, index, tmp->display);
		tmp = tmp->next;
	}
	free_env(sorted_env);
	g_global.exit = 0;
}

char	**print_unset_error(char *key, int *status)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(key, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	*status = 0;
	return (NULL);
}
