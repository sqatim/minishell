/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:35:52 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/21 15:31:08 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

static void changePathInExecStruct(t_execution *execStruct, t_env *env, char *path)
{
    t_env *node;

    if (execStruct->path)
    {
        free(execStruct->path);
        execStruct->path = NULL;
    }
    execStruct->path = ft_strdup(path);
    node = ft_getEnvNode(env, "PWD");
    if (node)
    {
        freeString(node->content);
        node->content = ft_strjoin("PWD=", path);
    }
}
static int changePathInExecStructInCaseOfError(t_execution *execStruct, t_env *env, char *path)
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
    node = ft_getEnvNode(env, "PWD");
    if (node)
    {
        freeString(node->content);
        node->content = ft_strjoin("PWD=", execStruct->path);
    }
    return 0;
}

char *checkCurrentPath(t_execution *execStruct)
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
t_env *changeOldPwdInEnv(t_execution *execStruct, t_env *env)
{
    char *buffer;
    t_env *node;
    char *pwd;
    t_env *tmp;

    tmp = env;
    buffer = checkCurrentPath(execStruct);
    if (buffer)
    {
        node = ft_getEnvNode(env, "OLDPWD");
        if (node)
        {
            freeString(node->content);
            node->content = ft_strjoin("OLDPWD=", buffer);
        }
        else
        {
            pwd = ft_strjoin("OLDPWD=", buffer);
            tmp = addEnvNode(tmp, pwd, 1);
            freeString(pwd);
        }
        free(buffer);
    }
    return tmp;
}

t_env *changeDirectory(t_execution *execStruct, t_env *env, char *path)
{
    t_env *tmp;
    char buffer[1024];
    char *pwd;

    tmp = env;
    if (!path)
        path = ft_getEnv(env, "HOME");
    if (path)
    {
        // to fix it when Home = \0
        tmp = changeOldPwdInEnv(execStruct, tmp);
        if (chdir(path) == 0)
        {
            if (!getcwd(buffer, 1024))
                changePathInExecStructInCaseOfError(execStruct, env, path);
            else
                changePathInExecStruct(execStruct, env, buffer);
        }
        else
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(path, 2);
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(errno), 2);
        }
    }
    else
        ft_putendl_fd("cd: HOME not set", 2);
    return (tmp);
}
