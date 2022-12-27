/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:58:46 by kernel            #+#    #+#             */
/*   Updated: 2022/12/27 19:36:22 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_env *setup_env(char **envp)
{
    int index;
    t_env *env;

    env = NULL;
    index = 0;
    while (envp[index])
    {
        env = add_env_node(env, envp[index], 1);
        index++;
    }
    return env;
}

void manage_command(t_execution *exec_struct, char *buffer)
{
    start_execution(exec_struct, exec_struct->command);
    free_string(buffer);
    buffer = NULL;
    if (exec_struct->command)
        exec_struct->command = free_command(exec_struct->command);
    if (exec_struct->redirections_sorted)
        exec_struct->redirections_sorted =
            free_redirection(exec_struct->redirections_sorted);
    return;
}

void minishell_loop(t_execution *exec_struct)
{
    char *buffer;
    int fd;

    signalHandler();
    while (1)
    {
        buffer = readline("minishell:> ");
        if (!buffer)
        {
            system("leaks minishell");
            ft_exit(exec_struct, 130);
        }
        if (buffer[0] != '\0')
        {
            // exec_struct->command = startParse(exec_struct->env, buffer);
            exec_struct->command = customizeMyParse(buffer);
            add_history(buffer);
            manage_command(exec_struct, buffer);
        }
        fd = open("/tmp/testFD", O_RDWR | O_CREAT);
        if (fd > 3)
            printf("FD LEAKS: fd => %d\n", fd);
        close(fd);
        // free_execution_struct(exec_struct);
    }
}

t_env *ft_get_env_node(t_env *env, char *key)
{
    t_env *tmp;
    int index;
    char *tmp_key;

    tmp = env;
    tmp_key = ft_strjoin(key, "=");
    index = 0;
    while (tmp)
    {
        if (ft_strnstr(tmp->content, tmp_key, ft_strlen(tmp_key)))
        {
            while (tmp->content[index] != '=')
                index++;
            free_string(tmp_key);
            return (tmp);
        }
        tmp = tmp->next;
    }
    return NULL;
}

char *ft_get_env(t_env *env, char *key)
{
    t_env *tmp;
    int index;
    char *tmp_key;

    tmp = env;
    tmp_key = ft_strjoin(key, "=");
    index = 0;
    while (tmp)
    {
        if (ft_strnstr(tmp->content, tmp_key, ft_strlen(tmp_key)))
        {
            while (tmp->content[index] != '=')
                index++;
            free_string(tmp_key);
            return (&tmp->content[++index]);
        }
        tmp = tmp->next;
    }
    free_string(tmp_key);
    return NULL;
}

int check_exit_argument_type(char *argument)
{
    int index;
    int type;
    int len;

    len = 0;
    index = 0;
    type = 1;
    if (argument[index] == '-' || argument[index] == '+')
    {
        if (argument[index == '-'])
            type = -1;
        index++;
        if (!argument[index])
            return (0);
    }
    while (argument[index])
    {
        if (!ft_isdigit(argument[index]))
            return 0;
        index++;
        len++;
    }
    if (len > 19)
        return (0);
    return type;
}