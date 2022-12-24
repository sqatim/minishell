/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:17:35 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/24 15:28:20 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int exec_input_redirection(t_redirection *input)
{
    int fd_input;
    char *path;

    if (!ft_strcmp(input->type, "<<"))
    {
        path = ft_strjoin("/tmp/", input->f_name);
        fd_input = open(path, O_RDWR, 0777);
        free_string(path);
        path = NULL;
    }
    else
        fd_input = open(input->f_name, O_RDWR, 0777);
    dup2(fd_input, STDIN_FILENO);
    close(fd_input);
    return (1);
}

int exec_output_redirection(t_redirection *output)
{
    int fd_output;

    if (!ft_strcmp(output->type, ">>"))
        fd_output = open(output->f_name, O_CREAT | O_APPEND | O_RDWR, 0777);
    else
        fd_output = open(output->f_name, O_CREAT | O_TRUNC | O_RDWR, 0777);
    dup2(fd_output, STDOUT_FILENO);
    close(fd_output);
    return (2);
}
