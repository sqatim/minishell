/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:17:35 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/13 17:51:59 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int execInputRedirection(t_redirection *input)
{
    int fdInput;
    char *path;

    if (!ft_strcmp(input->type, "<<"))
    {
        path = ft_strjoin("/tmp/", input->f_name);
        fdInput = open(path, O_RDWR, 0777);
        freeString(path);
        path = NULL;
    }
    else
        fdInput = open(input->f_name, O_RDWR, 0777);
    dup2(fdInput, STDIN_FILENO);
    close(fdInput);
    return (1);
}

int execOutputRedirection(t_redirection *output)
{
    int fdOutput;

    if (!ft_strcmp(output->type, ">>"))
        fdOutput = open(output->f_name, O_CREAT | O_APPEND | O_RDWR, 0777);
    else
        fdOutput = open(output->f_name, O_CREAT | O_TRUNC | O_RDWR, 0777);
    dup2(fdOutput, STDOUT_FILENO);
    close(fdOutput);
    return (2);
}
