/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:23:49 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/07 11:24:19 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int handleNewLineInEcho(char **argument, int *indexOne)
{
    int indexTwo;
    int check;

    check = 0;
    while (argument[*indexOne])
    {
        indexTwo = 2;
        if (argument[*indexOne][0] == '-' && argument[*indexOne][1] == 'n')
        {
            while (argument[*indexOne][indexTwo] == 'n' && argument[*indexOne][indexTwo])
                indexTwo++;
            if (!argument[*indexOne][indexTwo])
                check = 1;
            else
                break;
        }
        else
            break;
        (*indexOne)++;
    }
    return check;
}

void handleExitCases(int type, char **argument)
{
    unsigned long long number;
    int status;

    if (type == -1)
        number = ft_atoull(&argument[1][1]);
    else
        number = ft_atoull(argument[1]);
    if ((type == -1 && number > 9223372036854775808U) ||
        (type == 1 && number > 9223372036854775807))
        printExitError(2, argument[1]);
    else if (argument[1] && argument[2])
        printExitError(1, NULL);
    else
    {
        if (number > 256)
            status = number % 256;
        else
            status = number;
        if (type == -1)
            status = 256 - status;
        exit(status);
    }
}