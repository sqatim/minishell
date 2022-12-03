/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:21:27 by kernel            #+#    #+#             */
/*   Updated: 2022/12/03 14:35:00 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handleNoBuiltins(t_execution *execStruct, char **cmdLine)
{
    int id = fork();
    char cmd[] = "ls";
    char *argVec[] = {"ls", NULL};
    char *envVec[] = {"PATH=/bin"};
    if (id == 0)
    {
        // printf("wa fen a ba\n");
        if(execve(cmd, argVec, envVec) == -1)
            perror("Could not execute:");
    }
    else
    {
        wait(NULL);
    }
}