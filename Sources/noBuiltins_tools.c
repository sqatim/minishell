/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:37:25 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/07 11:24:19 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char *joinPathWithCommand(char *path, char *command)
{
    char *ptrToBeFreed;
    char *cmdJoined;
    
    cmdJoined = ft_strjoin(path, "/");
    ptrToBeFreed = cmdJoined;
    cmdJoined = ft_strjoin(cmdJoined, command);
    freeString(ptrToBeFreed);
    return cmdJoined;
}