/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:25:08 by kernel            #+#    #+#             */
/*   Updated: 2023/01/18 12:55:25 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	**extract_key_value(char *argument, int index)
{
	char	**key_value;

	key_value = (char **)calloc(4, sizeof(char *));
	if (argument[index] == '=' || (argument[index] == '+' && \
								argument[index + 1] == '='))
	{
		key_value[0] = ft_substr(argument, 0, index);
		if (argument[index] == '=')
		{
			key_value[1] = ft_strdup("=");
			key_value[2] = ft_substr(argument, index + 1, ft_strlen(argument));
		}
		else
		{
			key_value[1] = ft_strdup("+=");
			key_value[2] = ft_substr(argument, index + 2, ft_strlen(argument));
		}
	}
	else
		key_value[0] = ft_substr(argument, 0, ft_strlen(argument));
	return (key_value);
}

char	**parse_export_argument(char *argument, int *status)
{
	int	index;

	index = 0;
	if (!argument[index] || ft_isdigit(argument[index]))
		return (print_export_error(argument, status));
	while (argument[index] != '=' && argument[index])
	{
		if (argument[index] == '+' && argument[index + 1] == '=')
			break ;
		if (!ft_isalnum(argument[index]) && argument[index] != '_')
			return (print_export_error(argument, status));
		index++;
	}
	return (extract_key_value(argument, index));
}

char	*join_export_key_value(char **key_value, char *old_value)
{
	char	*joined;
	char	*old_with_new;
	char	*ptr_to_free;

	if (!ft_strcmp(key_value[1], "+="))
	{
		joined = ft_strjoin(key_value[0], "=");
		if (old_value)
			old_with_new = ft_strjoin(old_value, key_value[2]);
		else
			old_with_new = ft_strjoin("", key_value[2]);
		ptr_to_free = joined;
		joined = ft_strjoin(joined, old_with_new);
		free(ptr_to_free);
		free(old_with_new);
	}
	else
	{
		joined = ft_strjoin(key_value[0], "=");
		ptr_to_free = joined;
		joined = ft_strjoin(joined, key_value[2]);
		free(ptr_to_free);
	}
	return (joined);
}

t_env	*handle_export_key_value(t_execution *exec_struct, t_env *env, \
							t_export *export)
{
	export->old_value = ft_get_env(env, export->key_value[0]);
	if (export->old_value)
		export->old_value = ft_strdup(export->old_value);
	env = execute_unset_for_export(exec_struct, env, export->key_value[0]);
	export->key_value_joined = join_export_key_value(export->key_value, \
													export->old_value);
	env = add_env_node(env, export->key_value_joined, 1);
	return (env);
}

t_env	*handle_export(t_execution *exec_struct, t_env *env, char **argument)
{
	t_export	export;

	export = export_init();
	while (argument[export.index])
	{
		export.key_value = parse_export_argument(argument[export.index], \
												&export.status);
		if (export.key_value && !export.key_value[1])
		{
			if (!ft_get_node_env_without_exception(env, export.key_value[0]))
				env = add_env_node(env, export.key_value[0], 0);
		}
		else if (export.key_value && !export.key_value[3])
			env = handle_export_key_value(exec_struct, env, &export);
		export.index++;
		free_export_struct(&export);
	}
	if (export.status)
		g_global.exit = 0;
	else
		g_global.exit = 1;
	exec_struct->envArray = convert_env_to_array(exec_struct, env);
	return (env);
}
