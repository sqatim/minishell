/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:16:29 by kernel            #+#    #+#             */
/*   Updated: 2022/12/27 19:39:41 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_env *assign_env_node(t_env *node, char *key, char *value, char *key_value)
{
    node->name = ft_strdup(key);
    node->value = ft_strdup(value);
    node->content = ft_strdup(key_value);
    return (node);
}

void handle_shell_level_non_zero_case(t_env *node)
{
    char *itoa_number;
    int number;
    char *tmp;

    number = ft_atoi(node->value);
    free_env_node_content(node);
    if (number >= 0 && number <= 998)
    {
        itoa_number = ft_itoa(++number);
        tmp = itoa_number;
        itoa_number = ft_strjoin("SHLVL=", itoa_number);
        node = assign_env_node(node, "SHLVL", tmp, itoa_number);
        free(itoa_number);
        free(tmp);
    }
    else if (number > 998)
        node = assign_env_node(node, "SHLVL", "", "SHLVL=");
    else if (number < 0)
        node = assign_env_node(node, "SHLVL", "0", "SHLVL=0");
}

t_env *handle_shell_level(t_env *env)
{
    t_env *node;
    int type;

    node = ft_get_env_node(env, "SHLVL");
    if (!node)
        env = add_env_node(env, "SHLVL=1", 1);
    else
    {
        type = check_shell_lvl_value(node->value);
        if (!type)
        {
            free_env_node_content(node);
            node = assign_env_node(node, "SHLVL", "1", "SHLVL=1");
        }
        else
            handle_shell_level_non_zero_case(node);
    }
    return env;
}

t_execution *execution_initialization(char **envp)
{
    t_execution *exec_struct;

    exec_struct = ft_calloc(1, sizeof(t_execution));
    if (!exec_struct)
        exit(1);
    exec_struct->env = setup_env(envp);
    exec_struct->env = handle_shell_level(exec_struct->env);
    exec_struct->status = 0;
    exec_struct->command = NULL;
    exec_struct->redirections_sorted = NULL;
    exec_struct->path = NULL;
    exec_struct->envArray = NULL;
    exec_struct->envArray = convert_env_to_array(exec_struct,exec_struct->env);
    return exec_struct;
}

t_env *init_env(t_env *new, char *content, int display)
{
    int index;

    index = 0;
    if (display == 0)
    {
        new->name = ft_strdup(content);
        new->value = NULL;
    }
    else
    {
        while (content[index] != '=')
            index++;
        new->name = ft_substr(content, 0, index);
        new->value = ft_substr(content, ++index, ft_strlen(content));
    }
    new->content = ft_strdup(content);
    new->display = display;

    return (new);
}

t_env *add_env_node(t_env *head, char *content, int display)
{
    t_env *tmp;
    t_env *new;

    new = (t_env *)calloc(1, sizeof(t_env));
    // to handle ---------
    if (!new)
        exit(1);
    new = init_env(new, content, display);
    // new->name = keyvalue[]
    new->next = NULL;
    new->prev = NULL;
    if (!head)
        return new;
    tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
    return (head);
}