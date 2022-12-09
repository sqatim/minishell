/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputRedirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:55:06 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/09 19:48:45 by sqatim           ###   ########.fr       */
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
    path = ft_strjoin("./", filename);
    delimiter = ft_strjoin(filename, "\n");
    // path = ft_strjoin("/tmp", filename);
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

void inputFileRedirection()
{
}