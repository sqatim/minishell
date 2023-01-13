/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:25:08 by kernel            #+#    #+#             */
/*   Updated: 2023/01/13 16:17:46 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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

t_env	*env_clone(t_env *env)
{
	t_env	*new_env;
	t_env	*tmp;

	tmp = env;
	new_env = NULL;
	while (tmp)
	{
		new_env = add_env_node(new_env, tmp->content, tmp->display);
		tmp = tmp->next;
	}
	return (new_env);
}

void	iterate_and_sort_env(t_env **first_tmp)
{
	t_env	*second_tmp;
	char	*tmp;

	second_tmp = (*first_tmp)->next;
	while (second_tmp)
	{
		if (ft_strcmp(second_tmp->content, (*first_tmp)->content) < 0)
		{
			tmp = (*first_tmp)->content;
			(*first_tmp)->content = second_tmp->content;
			second_tmp->content = tmp;
		}
		second_tmp = second_tmp->next;
	}
	*first_tmp = (*first_tmp)->next;
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
		while (tmp->content[index] != '=')
			index++;
		print_env_with_export_second(tmp, &index);
		tmp = tmp->next;
	}
	free_env(sorted_env);
	g_global.exit = 0;
}

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
		joined = ft_strjoin(joined, old_with_new);
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
	env = execute_unset(exec_struct, env, export->key_value[0]);
	export->key_value_joined = join_export_key_value(export->key_value, \
			export->old_value);
	env = add_env_node(env, export->key_value_joined, 1);
	free_string(export->key_value_joined);
	export->key_value_joined = NULL;
	free_array_two_dimension(export->key_value);
	export->key_value = NULL;
	if (export->old_value)
		free_string(export->old_value);
	return (env);
}

t_env	*handle_export(t_execution *exec_struct, t_env *env, char **argument)
{
	t_export	export;

	export.status = 1;
	export.index = 1;
	while (argument[export.index])
	{
		export.key_value = parse_export_argument(argument[export.index], \
					&export.status);
		if (export.key_value && !export.key_value[1])
		{
			if (!ft_get_env(env, export.key_value[0]))
				env = add_env_node(env, export.key_value[0], 0);
		}
		else if (export.key_value && !export.key_value[3])
			env = handle_export_key_value(exec_struct, env, &export);
		export.index++;
	}
	if (export.status)
		g_global.exit = 0;
	else
		g_global.exit = 1;
	exec_struct->envArray = convert_env_to_array(exec_struct, env);
	return (env);
}
