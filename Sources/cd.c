/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:35:52 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/24 17:27:17 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

static void change_path_in_exec_struct(t_execution *execStruct, t_env *env, char *path)
{
    t_env *node;

    if (execStruct->path)
    {
        free(execStruct->path);
        execStruct->path = NULL;
    }
    execStruct->path = ft_strdup(path);
    node = ft_get_env_node(env, "PWD");
    if (node)
    {
        free_string(node->content);
        node->content = ft_strjoin("PWD=", path);
    }
}
static int change_path_in_exec_struct_in_case_of_error(t_execution *execStruct, t_env *env, char *path)
{
    char *tmp;
    t_env *node;

    tmp = execStruct->path;
    execStruct->path = ft_strjoin(tmp, "/");
    if (tmp)
    {
        free(tmp);
        tmp = NULL;
    }
    tmp = execStruct->path;
    execStruct->path = ft_strjoin(tmp, path);
    if (tmp)
    {
        free(tmp);
        tmp = NULL;
    }
    ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
    node = ft_get_env_node(env, "PWD");
    if (node)
    {
        free_string(node->content);
        node->content = ft_strjoin("PWD=", execStruct->path);
    }
    return 0;
}

char *check_current_path(t_execution *execStruct)
{
    char *buffer;

    buffer = ft_calloc(1024, sizeof(char));
    if (execStruct->path)
    {
        ft_strlcpy(buffer, execStruct->path, ft_strlen(execStruct->path) + 1);
        return buffer;
    }
    else if (getcwd(buffer, 1024))
        return buffer;
    return NULL;
}
t_env *change_old_pwd_in_env(t_execution *execStruct, t_env *env)
{
    char *buffer;
    t_env *node;
    char *pwd;
    t_env *tmp;

    tmp = env;
    buffer = check_current_path(execStruct);
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
    return tmp;
}

t_env *change_directory(t_execution *execStruct, t_env *env, char *path)
{
    t_env *tmp;
    char buffer[1024];
    int home;

    home = 0;
    tmp = env;
    if (!path)
        path = ft_get_env(env, "HOME");
    if (path)
    {
        // to fix it when Home = \0
        tmp = change_old_pwd_in_env(execStruct, tmp);
        if (!*path)
        {
            home = 1;
            path = ft_strdup(".");
        }
        if (chdir(path) == 0)
        {
            if (!getcwd(buffer, 1024))
                change_path_in_exec_struct_in_case_of_error(execStruct, env, path);
            else
                change_path_in_exec_struct(execStruct, env, buffer);
            g_global.exit = 0;
        }
        else
        {
            g_global.exit = 1;
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(path, 2);
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(errno), 2);
        }
        if (home == 1)
            free(path);
    }
    else
    {
        g_global.exit = 1;
        ft_putendl_fd("cd: HOME not set", 2);
    }
    return (tmp);
}
