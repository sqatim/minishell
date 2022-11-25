/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:47:37 by kernel            #+#    #+#             */
/*   Updated: 2022/11/26 00:41:26 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void executeEnv(t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        ft_putendl_fd(tmp->content, 1);
        tmp = tmp->next;
    }
}

t_env *executeUnset(t_env *env, char *argument)
{
    t_env *tmp;
    t_env *next;
    char *tmpArgument;

    if (argument)
    {
        tmpArgument = ft_strjoin(argument, "=");
        tmp = env;
        while (tmp)
        {
            if (ft_strnstr(tmp->content, tmpArgument, ft_strlen(tmpArgument)))
            {
                next = tmp->next;
                if (tmp->prev)
                    tmp->prev->next = tmp->next;
                if (tmp->next)
                    tmp->next->prev = tmp->prev;
                free(tmp);
                tmp = NULL;
                tmp = next;
                break;
            }
            else
                tmp = tmp->next;
        }
        if (tmp && !tmp->prev)
            env = tmp;
        free(tmpArgument);
        tmpArgument = NULL;
    }
    return env;
}

t_env *executeExport(t_env *env, char **argument)
{
    if (!argument[1])
        printEnvWithExport(env);
    else
        env = handleExport(env, argument);
    return env;
}

void executePwd()
{
    char buffer[1024];

    if (getcwd(buffer, 1024))
        ft_putendl_fd(buffer, 1);
    else
        ft_putendl_fd("error: in pwd", 2);
    // to handle --------------
}