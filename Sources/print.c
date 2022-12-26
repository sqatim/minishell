/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 23:10:39 by kernel            #+#    #+#             */
/*   Updated: 2022/12/26 17:11:06 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void print_exit_error(t_execution *exec_struct, int type, char *argument)
{
    ft_putendl_fd("exit", 1);
    ft_putstr_fd("minishell:> exit: ", 2);
    if (type == 1)
    {
        ft_putendl_fd("too many arguments", 2);
        g_global.exit = 1;
    }
    else
    {
        ft_putstr_fd(argument, 2);
        ft_putendl_fd(": numeric argument required", 2);
        ft_exit(exec_struct, 255);
    }
}

void print_error(char *cmd)
{
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    ft_putendl_fd(strerror(errno), 2);
}

char **print_export_error(char *key, int *status)
{
    ft_putstr_fd("export: `", 2);
    ft_putstr_fd(key, 2);
    ft_putendl_fd("': not a valid identifier", 2);
    *status = 0;
    return (NULL);
}

void print_cd_error(char *path, int type)
{
    g_global.exit = 1;
    if (type == 0)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
    }
    else
    {
        ft_putendl_fd("cd: HOME not set", 2);
    }
}

void print_fd_errors(char *file_name)
{
    ft_putstr_fd(file_name, 2);
    ft_putendl_fd(": No such file or directory", 2);
}