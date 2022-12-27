/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:41:04 by kernel            #+#    #+#             */
/*   Updated: 2022/12/27 18:49:58 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void free_array_two_dimension(char **array)
{
    int index;

    index = 0;
    if (array)
    {
        while (array[index])
        {
            free(array[index]);
            array[index] = NULL;
            index++;
        }
        free(array);
    }
}

void free_string(char *str)
{
    free(str);
    str = NULL;
}

t_redirection *free_redirection(t_redirection *redirection)
{
    if (!redirection)
        return NULL;
    free_redirection(redirection->next);
    free(redirection->f_name);
    free(redirection->type);
    redirection->f_name = NULL;
    redirection->type = NULL;
    free(redirection);
    redirection = NULL;
    return NULL;
}

void unlink_heredocument_files(t_redirection *redirections)
{
    t_redirection *tmp;
    char *path;

    tmp = redirections;
    while (tmp)
    {
        if (!ft_strcmp(tmp->type, "<<"))
        {
            path = ft_strjoin("/tmp/", tmp->f_name);
            unlink(path);
            free(path);
        }
        tmp = tmp->next;
    }
}

void free_env(t_env *env)
{
    if (!env)
        return;
    free_env(env->next);
    free(env->content);
    free(env->value);
    free(env->name);
    env->content = NULL;
    env->value = NULL;
    env->name = NULL;
    free(env);
    env = NULL;
}

t_command *free_command(t_command *command)
{
    if (!command)
        return NULL;
    free_command(command->next);
    free_array_two_dimension(command->command);
    unlink_heredocument_files(command->redirections);
    free_redirection(command->redirections);
    free(command);
    command = NULL;
    return NULL;
}

void free_execution_struct(t_execution *exec_struct)
{
    if (exec_struct)
    {
        if (exec_struct->redirections_sorted)
            free_redirection(exec_struct->redirections_sorted);
        if (exec_struct->command)
            free_command(exec_struct->command);
        if (exec_struct->env)
            free_env(exec_struct->env);
        if (exec_struct->path)
            free_string(exec_struct->path);
        if (exec_struct->envArray)
            free_array_two_dimension(exec_struct->envArray);
        free(exec_struct);
    }
}

void free_env_node_content(t_env *node)
{
    if (node->content)
    {
        free(node->content);
        node->content = NULL;
    }
    if (node->name)
    {
        free(node->name);
        node->name = NULL;
    }
    if (node->value)
    {
        free(node->value);
        node->value = NULL;
    }
}