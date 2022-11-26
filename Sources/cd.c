/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:35:52 by sqatim            #+#    #+#             */
/*   Updated: 2022/11/26 18:04:38 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void changeDirectory(t_env *env, char *path)
{
    if(!path)
        path = ft_getEnv(env, "HOME");
    if (path)
    {
        if (chdir(path) == -1)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(path, 2);
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(errno), 2);
        }
    }
    else
        ft_putendl_fd("cd: HOME not set", 2);
}
