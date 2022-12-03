/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 23:10:39 by kernel            #+#    #+#             */
/*   Updated: 2022/12/03 20:15:03 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printExitError(int type, char *argument)
{
    ft_putendl_fd("exit", 1);
    ft_putstr_fd("minishell:> exit: ", 2);
    if (type == 1)
        ft_putendl_fd("too many arguments", 2);
    else
    {
        ft_putstr_fd(argument,2);
        ft_putendl_fd(": numeric argument required", 2);
        exit(2);
    }
}

void printError(char *cmd)
{
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    ft_putendl_fd(strerror(errno), 2);
}