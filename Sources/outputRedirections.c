/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputRedirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:56:28 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/09 20:16:34 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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