/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:35:52 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/13 15:45:40 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

static void	change_path_in_exec_struct(t_execution *exec_struct, t_env *env, \
			char *path)
{
	t_env	*node;

	if (exec_struct->path)
	{
		free(exec_struct->path);
		exec_struct->path = NULL;
	}
	exec_struct->path = ft_strdup(path);
	node = ft_get_env_node(env, "PWD");
	if (node)
	{
		free_string(node->content);
		node->content = ft_strjoin("PWD=", path);
	}
}

void	change_path_in_exec_struct_in_case_of_error(t_execution *exec_struct, \
						t_env *env, char *path)
{
	char	*tmp;

	tmp = exec_struct->path;
	exec_struct->path = ft_strjoin(tmp, "/");
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	tmp = exec_struct->path;
	exec_struct->path = ft_strjoin(tmp, path);
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot \
		access parent directories: No such file or directory", 2);
	change_pwd_in_env_in_case_of_error(exec_struct, env);
}

t_env	*change_old_pwd_in_env(t_execution *exec_struct, t_env *env)
{
	t_env	*node;
	t_env	*tmp;
	char	*buffer;
	char	*pwd;

	tmp = env;
	buffer = check_current_path(exec_struct);
	if (buffer)
	{
		node = ft_get_env_node(env, "OLDPWD");
		if (node)
		{
			free_string(node->content);
			node->content = ft_strjoin("OLDPWD=", buffer);
		}
		else
		{
			pwd = ft_strjoin("OLDPWD=", buffer);
			tmp = add_env_node(tmp, pwd, 1);
			free_string(pwd);
		}
		free(buffer);
	}
	return (tmp);
}

void	handle_change_directory(t_execution *exec_struct, t_env *env, \
						char *path, int home)
{
	char	buffer[1024];

	if (chdir(path) == 0)
	{
		if (!getcwd(buffer, 1024))
			change_path_in_exec_struct_in_case_of_error(exec_struct, env, path);
		else
			change_path_in_exec_struct(exec_struct, env, buffer);
		g_global.exit = 0;
	}
	else
		print_cd_error(path, 0);
	if (home == 1)
		free(path);
}

t_env	*change_directory(t_execution *exec_struct, t_env *env, char *path)
{
	t_env	*tmp;
	int		home;

	home = 0;
	tmp = env;
	if (!path)
		path = ft_get_env(env, "HOME");
	if (path)
	{
		tmp = change_old_pwd_in_env(exec_struct, tmp);
		if (!*path)
		{
			home = 1;
			path = ft_strdup(".");
		}
		handle_change_directory(exec_struct, env, path, home);
	}
	else
		print_cd_error(path, 1);
	return (tmp);
}
