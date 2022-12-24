/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:25:08 by kernel            #+#    #+#             */
/*   Updated: 2022/12/24 17:30:39 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;

    i = 0;
    if ((!s1 || !s2))
        return (-1);
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    if (((s1[i] == '\0' && s2[i] != '\0') || (s2[i] == '\0' && s1[i] != '\0')))
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    return (0);
}

t_env *env_clone(t_env *env)
{
    t_env *tmp;
    t_env *new_env;

    tmp = env;
    new_env = NULL;
    while (tmp)
    {
        new_env = add_env_node(new_env, tmp->content, tmp->display);
        tmp = tmp->next;
    }
    return (new_env);
}

t_env *sort_env(t_env *env)
{
    t_env *first_tmp;
    t_env *second_tmp;
    t_env *env_export;
    char *tmp;

    env_export = env_clone(env);
    if (env_export)
    {
        first_tmp = env_export;
        second_tmp = env_export;
        while (first_tmp->next)
        {
            second_tmp = first_tmp->next;
            while (second_tmp)
            {
                if (ft_strcmp(second_tmp->content, first_tmp->content) < 0)
                {
                    tmp = first_tmp->content;
                    first_tmp->content = second_tmp->content;
                    second_tmp->content = tmp;
                }
                second_tmp = second_tmp->next;
            }
            first_tmp = first_tmp->next;
        }
    }
    return env_export;
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

void print_env_with_export(t_env *env)
{
    t_env *sorted_env;
    int index;
    char *key;
    char *value;

    sorted_env = sort_env(env);
    while (sorted_env)
    {
        index = 0;
        while (sorted_env->content[index] != '=')
            index++;
        key = ft_substr(sorted_env->content, 0, ++index);
        value = ft_substr(sorted_env->content, index, ft_strlen(sorted_env->content));

        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(key, 1);
        ft_putstr_fd("\"", 1);
        print_value_of_export(value);
        ft_putendl_fd("\"", 1);
        sorted_env = sorted_env->next;
    }
    free_env(sorted_env);
    g_global.exit = 0;
}

char **parse_export_argument(char *argument, int *status)
{
    char **key_value;
    int index;

    index = 0;
    if (!argument[index] || ft_isdigit(argument[index]))
        return print_export_error(argument, status);
    while (argument[index] != '=' && argument[index])
    {
        if (argument[index] == '+' && argument[index + 1] == '=')
            break;
        if (!ft_isalnum(argument[index]) && argument[index] != '_')
            return print_export_error(argument, status);
        index++;
    }
    key_value = (char **)calloc(4, sizeof(char *));
    if (argument[index] == '=' || (argument[index] == '+' && argument[index + 1] == '='))
    {
        key_value[0] = ft_substr(argument, 0, index);
        if (argument[index] == '=')
        {
            key_value[1] = ft_strdup("=");
            key_value[2] = ft_substr(argument, index + 1, ft_strlen(argument));
        }
        else
        {
            key_value[1] = ft_strdup("+=");
            key_value[2] = ft_substr(argument, index + 2, ft_strlen(argument));
        }
    }
    else
        key_value[0] = ft_substr(argument, 0, ft_strlen(argument));
    return (key_value);
}

char *join_export_key_value(char **key_value, char *old_value)
{
    char *joined;
    char *old_with_new;

    if (!ft_strcmp(key_value[1], "+="))
    {
        joined = ft_strjoin(key_value[0], "=");
        if (old_value)
            old_with_new = ft_strjoin(old_value, key_value[2]);
        else
            old_with_new = ft_strjoin("", key_value[2]);
        joined = ft_strjoin(joined, old_with_new);
    }
    else
    {
        joined = ft_strjoin(key_value[0], "=");
        joined = ft_strjoin(joined, key_value[2]);
    }
    return joined;
}

t_env *handle_export(t_env *env, char **argument)
{
    t_export export;

    export.status = 1;
    export.index = 1;
    while (argument[export.index])
    {
        export.key_value = parse_export_argument(argument[export.index], &export.status);
        if (export.key_value && !export.key_value[1])
        {
            if (!ft_get_env(env, export.key_value[0]))
                env = add_env_node(env, export.key_value[0], 0);
        }
        else if (export.key_value && !export.key_value[3])
        {
            export.old_value = ft_get_env(env, export.key_value[0]);
            if (export.old_value)
                export.old_value = ft_strdup(export.old_value);
            env = execute_unset(env, export.key_value[0]);
            export.key_value_joined = join_export_key_value(export.key_value, export.old_value);
            env = add_env_node(env, export.key_value_joined, 1);
            free_string(export.key_value_joined);
            free_array_two_dimension(export.key_value);
        }
        export.index++;
    }
    if (export.status)
        g_global.exit = 0;
    else
        g_global.exit = 1;
    return env;
}