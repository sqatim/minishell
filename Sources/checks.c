/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:50:47 by kernel            #+#    #+#             */
/*   Updated: 2022/11/24 22:30:46 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void checkCommand(char **cmdLine, t_execution *execStruct)
{
    if(ft_strnstr("env",cmdLine[0], 3))
        executeEnv(execStruct->env);
    else if(ft_strnstr("export",cmdLine[0], 6))
        printf("export\n");
    else if(ft_strnstr("unset",cmdLine[0], 5))
        printf("unset\n");
    else if(ft_strnstr("cd",cmdLine[0], 2))
        printf("cd\n");
    else if(ft_strnstr("pwd",cmdLine[0], 3))
        printf("pwd\n");
    else if(ft_strnstr("echo",cmdLine[0], 4))
        printf("echo\n");
    else if(ft_strnstr("exit",cmdLine[0], 4))
        printf("exit\n");
    else
        printf("no Builtins command\n");
    
}