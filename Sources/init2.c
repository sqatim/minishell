/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:56:34 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/17 18:57:23 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	handle_shell_level_non_zero_case(t_env *node)
{
	char	*itoa_number;
	char	*tmp;
	int		number;

	number = ft_atoi(node->value);
	free_env_node_content(node);
	if (number >= 0 && number <= 998)
	{
		itoa_number = ft_itoa(++number);
		tmp = itoa_number;
		itoa_number = ft_strjoin("SHLVL=", itoa_number);
		node = assign_env_node(node, "SHLVL", tmp, itoa_number);
		free(itoa_number);
		free(tmp);
	}
	else if (number > 998)
		node = assign_env_node(node, "SHLVL", "", "SHLVL=");
	else if (number < 0)
		node = assign_env_node(node, "SHLVL", "0", "SHLVL=0");
}

t_env	*handle_shell_level(t_env *env)
{
	t_env	*node;
	int		type;

	node = ft_get_env_node(env, "SHLVL");
	if (!node)
		env = add_env_node(env, "SHLVL=1", 1);
	else
	{
		type = check_shell_lvl_value(node->value);
		if (!type)
		{
			free_env_node_content(node);
			node = assign_env_node(node, "SHLVL", "1", "SHLVL=1");
		}
		else
			handle_shell_level_non_zero_case(node);
	}
	return (env);
}

t_execution	*execution_initialization(char **envp)
{
	t_execution	*exec_struct;

	exec_struct = ft_calloc(1, sizeof(t_execution));
	if (!exec_struct)
		exit(1);
	exec_struct->env = setup_env(envp);
	exec_struct->env = handle_shell_level(exec_struct->env);
	exec_struct->status = 0;
	exec_struct->command = NULL;
	exec_struct->redirections_sorted = NULL;
	exec_struct->path = NULL;
	exec_struct->envArray = NULL;
	exec_struct->envArray = convert_env_to_array(exec_struct, exec_struct->env);
	return (exec_struct);
}
