/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:41:04 by kernel            #+#    #+#             */
/*   Updated: 2023/01/18 21:28:09 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	free_array_two_dimension(char **array)
{
	int	index;

	index = 0;
	if (array)
	{
		while (array[index])
		{
			free(array[index]);
			array[index] = NULL;
			index++;
		}
		free(array);
	}
}

void	free_string(char *str)
{
	free(str);
	str = NULL;
}

t_redirection	*free_redirection(t_redirection *redirection)
{
	if (!redirection)
		return (NULL);
	free_redirection(redirection->next);
	free(redirection->f_name);
	free(redirection->type);
	redirection->f_name = NULL;
	redirection->type = NULL;
	free(redirection);
	redirection = NULL;
	return (NULL);
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	free_env(env->next);
	free(env->content);
	free(env->value);
	free(env->name);
	env->content = NULL;
	env->value = NULL;
	env->name = NULL;
	free(env);
	env = NULL;
}

void	free_execution_struct(t_execution *exec_struct)
{
	if (exec_struct)
	{
		if (exec_struct->redirections_sorted)
			free_redirection(exec_struct->redirections_sorted);
		if (exec_struct->command)
			free_command(exec_struct->command);
		if (exec_struct->env)
			free_env(exec_struct->env);
		if (exec_struct->path)
			free_string(exec_struct->path);
		if (exec_struct->envArray)
			free_array_two_dimension(exec_struct->envArray);
		free(exec_struct);
	}
}
