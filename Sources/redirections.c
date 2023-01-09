/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:07:22 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/09 14:22:20 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void printRedirection(t_redirection *redirections)
{
    t_redirection *tmp = redirections;

    while (tmp)
    {
        printf("%s %s\n", tmp->type, tmp->f_name);
        tmp = tmp->next;
    }
}

void here_document_redirection(char *filename, t_env *env)
{
    int fd;
    char *path;
    char *buffer;
    char *delimiter;
    int len;

    buffer = ft_calloc(BUFFER_SIZE, 1);
    // path = ft_strjoin("./", filename);
    path = ft_strjoin("/tmp/", filename);
    delimiter = ft_strjoin(filename, "\n");
    fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0777);
    g_global.here_doc = 1;

    while (ft_strcmp(buffer, delimiter) != 0)
    {
        len = read(0, buffer, BUFFER_SIZE);
        buffer[len] = '\0';
        while (search_dollar(buffer) == 1)
            expand_after_dollar_h(&buffer, env);
        // printf("delimter: %s\n", delimiter);
        if (ft_strcmp(buffer, delimiter) != 0)
            write(fd, buffer, len);
    }
    g_global.here_doc = 0;
    free_string(delimiter);
    free_string(path);
    free(buffer);
    buffer = NULL;
    path = NULL;
    delimiter = NULL;
    close(fd);
}

void ouput_trunc_redirection(char *filename)
{
    int fd;

    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
    close(fd);
}

void output_append_redirection(char *filename)
{
    int fd;

    fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0777);
    close(fd);
}

int check_input_redirection(t_redirection *redirections, int *check)
{
    t_redirection *tmp;
    int fd;

    tmp = redirections;
    while (tmp)
    {
        if (!ft_strcmp(tmp->type, "<"))
        {
            fd = open(tmp->f_name, O_RDONLY, 0777);
            if (fd == -1)
            {
                print_fd_errors(tmp->f_name);
                g_global.exit = 1;
                *check = 0;
                return (0);
            }
            close(fd);
        }
        tmp = tmp->next;
    }
    return 1;
}

t_redirection *handle_redirection(t_env *env, t_redirection *redirections, int *check)
{
    t_redirection *last_redirections;
    t_redirection *tmp;

    tmp = redirections;
    // printf("tmp -> %s\n", tmp->type);
    while (tmp)
    {
        if (!ft_strcmp(tmp->type, "<<"))
            here_document_redirection(tmp->f_name, env);
        tmp = tmp->next;
    }
    if (!check_input_redirection(redirections, check))
        return NULL;
    tmp = redirections;
    while (tmp)
    {
        if (!ft_strcmp(tmp->type, ">>"))
            output_append_redirection(tmp->f_name);
        else if (!ft_strcmp(tmp->type, ">"))
            ouput_trunc_redirection(tmp->f_name);
        tmp = tmp->next;
    }
    last_redirections = setup_the_last_redirections(redirections);
    // printRedirection(last_redirections);
    return last_redirections;
}