/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:37:25 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/13 16:34:39 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char	*join_path_with_command(char *path, char *command)
{
	char	*ptr_to_be_freed;
	char	*cmd_joined;

	cmd_joined = ft_strjoin(path, "/");
	ptr_to_be_freed = cmd_joined;
	cmd_joined = ft_strjoin(cmd_joined, command);
	free_string(ptr_to_be_freed);
	return (cmd_joined);
}

int	env_linked_list_len(t_env *env)
{
	t_env	*tmp;
	int		index;

	index = 0;
	tmp = env;
	while (tmp)
	{
		index++;
		tmp = tmp->next;
	}
	return (index);
}

int	env_linked_list_len_with_key_value(t_env *env)
{
	t_env	*tmp;
	int		index;

	index = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->display)
			index++;
		tmp = tmp->next;
	}
	return (index);
}

char	**convert_env_to_array(t_execution *exec_struct, t_env *env)
{
	t_env	*tmp;
	char	**env_array;
	int		index;
	int		len;

	index = 0;
	len = env_linked_list_len_with_key_value(env);
	if (exec_struct->envArray)
		free_array_two_dimension(exec_struct->envArray);
	if (len == 0)
		return (NULL);
	env_array = ft_calloc(++len, sizeof(char *));
	tmp = env;
	while (tmp)
	{
		env_array[index++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (env_array);
}
