/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:37:25 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/24 15:37:37 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char *join_path_with_command(char *path, char *command)
{
    char *ptr_to_be_freed;
    char *cmd_joined;

    cmd_joined = ft_strjoin(path, "/");
    ptr_to_be_freed = cmd_joined;
    cmd_joined = ft_strjoin(cmd_joined, command);
    free_string(ptr_to_be_freed);
    return cmd_joined;
}

int env_linked_list_len(t_env *env)
{
    t_env *tmp;
    int index;

    index = 0;
    tmp = env;
    while (tmp)
    {
        index++;
        tmp = tmp->next;
    }
    return (index);
}

char **convert_env_to_array(t_env *env)
{
    char **env_array;
    int index;
    int len;
    t_env *tmp;

    index = 0;
    len = env_linked_list_len(env);
    env_array = ft_calloc(++len, sizeof(char *));
    tmp = env;
    while (tmp)
    {
        env_array[index++] = ft_strdup(tmp->content);
        tmp = tmp->next;
    }
    return env_array;
}