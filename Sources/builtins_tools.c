/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:23:49 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/24 18:44:36 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int handle_new_line_in_echo(char **argument, int *indexOne)
{
    int indexTwo;
    int check;

    check = 0;
    while (argument[*indexOne])
    {
        indexTwo = 2;
        if (argument[*indexOne][0] == '-' && argument[*indexOne][1] == 'n')
        {
            while (argument[*indexOne][indexTwo] == 'n' &&\
                 argument[*indexOne][indexTwo])
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

void handle_exit_cases(t_execution *exec_struct, int type, char **argument)
{
    unsigned long long number;
    int status;

    if (type == -1)
        number = ft_atoull(&argument[1][1]);
    else
        number = ft_atoull(argument[1]);
    if ((type == -1 && number > 9223372036854775808U) ||
        (type == 1 && number > 9223372036854775807))
        print_exit_error(exec_struct, 2, argument[1]);
    else if (argument[1] && argument[2])
        print_exit_error(exec_struct, 1, NULL);
    else
    {
        if (number > 256)
            status = number % 256;
        else
            status = number;
        if (type == -1)
            status = 256 - status;
        ft_exit(exec_struct, status);
    }
}

void ft_exit(t_execution *exec_struct, int status)
{
    free_execution_struct(exec_struct);
    exit(status);
}