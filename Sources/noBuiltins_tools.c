/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noBuiltins_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 20:37:25 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/03 20:42:12 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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