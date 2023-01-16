/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseCustomized.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:03:17 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/16 19:39:01 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

static t_command *parseNewCommand(t_command *head, char **command, int size)
{
    t_command *tmp = head;
    t_command *new = NULL;
    int index = 0;

    new = ft_calloc(1, sizeof(t_command));
    new->command = ft_calloc(size + 1, sizeof(char *));
    while (index < size)
    {
        new->command[index] = ft_strdup(command[index]);
        index++;
    }
    new->redirections = NULL;
    new->next = NULL;
    if (!head)
        return new;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return head;
}

static t_redirection *parseRedirections(t_redirection *head, char **bufferParsed)
{
    t_redirection *tmp = head;
    t_redirection *new;

    new = ft_calloc(1, sizeof(t_redirection));
    new->next = NULL;
    new->type = ft_strdup(bufferParsed[0]);
    new->f_name = ft_strdup(bufferParsed[1]);
    if (!head)
        return new;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return head;
}

t_command *customizeMyParse(char *buffer)
{
    char **bufferParsed = NULL;
    char **commandParsed = NULL;
    t_command *command = NULL;
    t_command *tmp = NULL;

    int index = 0;
    int indexCommand = 0;
    commandParsed = ft_split(buffer, '|');
    while (commandParsed[indexCommand])
    {
        index = 0;
        bufferParsed = ft_split(commandParsed[indexCommand], ' ');
        while (ft_strcmp(bufferParsed[index], ">") && ft_strcmp(bufferParsed[index], ">>") &&
               ft_strcmp(bufferParsed[index], "<") && ft_strcmp(bufferParsed[index], "<<") && bufferParsed[index])
            index++;
        command = parseNewCommand(command, bufferParsed, index);
        tmp = command;
        while (tmp->next)
            tmp = tmp->next;
        while (bufferParsed[index])
        {
            tmp->redirections = parseRedirections(tmp->redirections, &bufferParsed[index]);
            index += 2;
        }
        indexCommand++;
        free_array_two_dimension(bufferParsed);
    }
    free_array_two_dimension(commandParsed);
    return command;
}
