/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:23:49 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/13 15:25:55 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int	handle_new_line_in_echo(char **argument, int *index_one)
{
	int	index_two;
	int	check;

	check = 0;
	while (argument[*index_one])
	{
		index_two = 2;
		if (argument[*index_one][0] == '-' && argument[*index_one][1] == 'n')
		{
			while (argument[*index_one][index_two] == 'n' && \
				argument[*index_one][index_two])
				index_two++;
			if (!argument[*index_one][index_two])
				check = 1;
			else
				break ;
		}
		else
			break ;
		(*index_one)++;
	}
	return (check);
}

void	handle_exit_cases(t_execution *exec_struct, int type, char **argument)
{
	unsigned long long	number;
	int					status;

	if (type == -1)
		number = ft_atoull(&argument[1][1]);
	else
		number = ft_atoull(argument[1]);
	if ((type == -1 && number > 9223372036854775808U) || \
		(type == 1 && number > 9223372036854775807))
		print_exit_error(exec_struct, 2, argument[1]);
	else if (argument[1] && argument[2])
		print_exit_error(exec_struct, 1, NULL);
	else
	{
		if (number > 256)
			status = number % 256;
		else
			status = number;
		if (type == -1)
			status = 256 - status;
		ft_exit(exec_struct, status);
	}
}

char	*check_current_path(t_execution *execStruct)
{
	char	*buffer;

	buffer = ft_calloc(1024, sizeof(char));
	if (execStruct->path)
	{
		ft_strlcpy(buffer, execStruct->path, ft_strlen(execStruct->path) + 1);
		return (buffer);
	}
	else if (getcwd(buffer, 1024))
		return (buffer);
	return (NULL);
}

void	ft_exit(t_execution *exec_struct, int status)
{
	free_execution_struct(exec_struct);
	exit(status);
}

void	change_pwd_in_env_in_case_of_error(t_execution *exec_struct, t_env *env)
{
	t_env	*node;

	node = ft_get_env_node(env, "PWD");
	if (node)
	{
		free_string(node->content);
		node->content = ft_strjoin("PWD=", exec_struct->path);
	}
}
