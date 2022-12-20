/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:35:52 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/16 20:38:38 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_env *changePwdInEnv(t_env *env, char *path)
{
}

t_env *changeDirectory(t_env *env, char *path)
{
    t_env *tmp;
    char buffer[1024];
    t_env *node;
    char *pwd;

    tmp = env;
    if (!path)
        path = ft_getEnv(env, "HOME");
    if (path)
    {
        // if (getcwd(buffer, 1024))
        // {
        //     node = ft_getEnvNode(env, "OLDPWD");
        //     if (node)
        //     {
        //         freeString(node->content);
        //         node->content = ft_strjoin("OLDPWD=", buffer);
        //     }
        //     else
        //     {
        //         pwd = ft_strjoin("OLDPWD=", buffer);
        //         tmp = addEnvNode(tmp, pwd, 1);
        //         freeString(pwd);
        //         pwd = NULL;
        //     }
        // }
        // else
        // {
        //     ft_putendl_fd("makaynshe", 2);
        // }
        if (chdir(path) == 0)
        {
            getcwd(buffer, 1024);
            node = ft_getEnvNode(env, "PWD");
            if (node)
            {
                freeString(node->content);
                node->content = ft_strjoin("PWD=", buffer);
            }
            else
            {
                pwd = ft_strjoin("PWD=", buffer);
                tmp = addEnvNode(tmp, pwd, 1);
                freeString(pwd);
                pwd = NULL;
            }
        }
        else
        {
            ft_putstr_fd("toto: ", 2);
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
