/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:49:40 by samirqatim        #+#    #+#             */
/*   Updated: 2023/01/17 20:57:17 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	execute_cd(t_execution *exec_struct, t_env *env, char **argument)
{
	if (!argument[1])
		exec_struct->env = change_directory(exec_struct, env, NULL);
	else
		exec_struct->env = change_directory(exec_struct, env, argument[1]);
}

void	execute_echo(char **argument)
{
	int	index_one;
	int	check;

	index_one = 1;
	check = handle_new_line_in_echo(argument, &index_one);
	while (argument[index_one])
	{
		ft_putstr_fd(argument[index_one], 1);
		if (argument[index_one + 1])
			ft_putchar_fd(' ', 1);
		index_one++;
	}
	if (check == 0)
		ft_putchar_fd('\n', 1);
	g_global.exit = 0;
}

void	execute_exit(t_execution *exec_struct, char **argument)
{
	int	type;

	if (!argument[1])
		exit(g_global.exit);
	else
	{
		type = check_exit_argument_type(argument[1]);
		if (type == 0)
			print_exit_error(exec_struct, 2, argument[1]);
		else
			handle_exit_cases(exec_struct, type, argument);
	}
}

void	execute_pwd(t_execution *exec_struct)
{
	char	buffer[1024];

	if (exec_struct->path)
		ft_putendl_fd(exec_struct->path, 1);
	else
	{
		if (getcwd(buffer, 1024))
			ft_putendl_fd(buffer, 1);
		else
			ft_putendl_fd("error: in pwd", 2);
	}
	g_global.exit = 0;
}

t_env	*execute_export(t_execution *exec_struct, t_env *env, char **argument)
{
	if (!argument[1])
		print_env_with_export(env);
	else
	{
		if (argument[1][0] == '#')
			print_env_with_export(env);
		else
			env = handle_export(exec_struct, env, argument);
	}
	return (env);
}
