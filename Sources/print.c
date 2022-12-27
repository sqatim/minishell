/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 23:10:39 by kernel            #+#    #+#             */
/*   Updated: 2022/12/27 19:49:37 by samirqatim       ###   ########.fr       */
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

void print_value_of_export(char *value)
{
    int index;

    index = 0;
    while (value[index])
    {
        if (value[index] == '"')
            ft_putchar_fd('\\', 1);
        ft_putchar_fd(value[index], 1);
        index++;
    }
}

void print_env_with_export_second(t_env *sorted_env, int *index)
{
    char *key;
    char *value;

    key = ft_substr(sorted_env->content, 0, ++(*index));
    value = ft_substr(sorted_env->content, *index,
                      ft_strlen(sorted_env->content));
    ft_putstr_fd("declare -x ", 1);
    ft_putstr_fd(key, 1);
    ft_putstr_fd("\"", 1);
    print_value_of_export(value);
    ft_putendl_fd("\"", 1);
    free(key);
    free(value);
}