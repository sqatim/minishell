/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:07:22 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/26 17:12:35 by samirqatim       ###   ########.fr       */
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

void here_document_redirection(char *filename)
{
    int fd;
    char *path;
    char *buffer;
    char *delimiter;
    int len;

    buffer = ft_calloc(BUFFER_SIZE, 1);
    path = ft_strjoin("/tmp/", filename);
    delimiter = ft_strjoin(filename, "\n");
    fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0777);
    while (ft_strcmp(buffer, delimiter) != 0)
    {
        len = read(0, buffer, BUFFER_SIZE);
        buffer[len] = '\0';
        if (ft_strcmp(buffer, delimiter) != 0)
            write(fd, buffer, len);
    }
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

t_redirection *handle_redirection(t_redirection *redirections, int *check)
{
    t_redirection *last_redirections;
    t_redirection *tmp;

    tmp = redirections;
    while (tmp)
    {
        if (!ft_strcmp(tmp->type, "<<"))
            here_document_redirection(tmp->f_name);
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