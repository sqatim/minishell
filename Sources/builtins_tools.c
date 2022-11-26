/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:23:49 by sqatim            #+#    #+#             */
/*   Updated: 2022/11/26 19:13:32 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void exitFromMinishell(int number)
{
    
}