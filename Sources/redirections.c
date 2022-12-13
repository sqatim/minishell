/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:07:22 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/13 17:16:39 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void hereDocumentRedirection(char *filename)
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
    while (ft_strcmp(buffer, delimiter) != 0)
    {
        len = read(0, buffer, BUFFER_SIZE);
        buffer[len] = '\0';
        if (ft_strcmp(buffer, delimiter) != 0)
            write(fd, buffer, len);
    }
    freeString(delimiter);
    freeString(path);
    free(buffer);
    buffer = NULL;
    path = NULL;
    delimiter = NULL;
}

void ouputTruncRedirection(char *filename)
{
    int fd;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0777);
    close(fd);
}

void outputAppendRedirection(char *filename)
{
    int fd;

    fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0777);
    close(fd);
}

t_redirection *handleRedirection(t_redirection *redirections)
{
    t_redirection *lastRedirections;
    t_redirection *tmp;

    tmp = redirections;
    while (tmp)
    {
        if (!ft_strcmp(tmp->type, "<<"))
            hereDocumentRedirection(tmp->f_name);
        tmp = tmp->next;
    }
    tmp = redirections;
    while (tmp)
    {
        if (!ft_strcmp(tmp->type, ">>"))
            outputAppendRedirection(tmp->f_name);
        else if (!ft_strcmp(tmp->type, ">"))
            ouputTruncRedirection(tmp->f_name);
        tmp = tmp->next;
    }
    lastRedirections = setupTheLastRedirections(redirections, redirections);
    return lastRedirections;
}