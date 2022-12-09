/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseCustomized.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:03:17 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/09 20:42:51 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

static void printCommand(t_command *command)
{
    int index;
    t_redirection *tmp;
    t_command *commandTmp;

    commandTmp = command;
    while (command)
    {
        index = 0;
        while (command->word_cmd[index])
        {
            printf("%s", command->word_cmd[index]);
            index++;
            !command->word_cmd[index] ? printf("\n") : printf(" ");
        }
        tmp = command->redirections;
        if (tmp)
            printf("Redirections\n");
        while (tmp)
        {
            printf("%s %s\n", tmp->type, tmp->f_name);
            tmp = tmp->next;
        }
        command = command->next;
    }
    command = commandTmp;
}

static t_command *parseNewCommand(t_command *head, char **command, int size)
{
    t_command *tmp = head;
    t_command *new = NULL;
    int index = 0;

    new = ft_calloc(1, sizeof(t_command));
    new->word_cmd = ft_calloc(size + 1, sizeof(char *));
    while (index < size)
    {
        new->word_cmd[index] = ft_strdup(command[index]);
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

    int index = 0;
    int indexCommand = 0;
    commandParsed = ft_split(buffer, '|');
    while (commandParsed[indexCommand])
    {
        index = 0;
        bufferParsed = ft_split(buffer, ' ');
        while (ft_strcmp(bufferParsed[index], ">") && ft_strcmp(bufferParsed[index], ">>") &&
               ft_strcmp(bufferParsed[index], "<") && ft_strcmp(bufferParsed[index], "<<") && bufferParsed[index])
            index++;
        command = parseNewCommand(command, bufferParsed, index);

        while (bufferParsed[index])
        {
            command->redirections = parseRedirections(command->redirections, &bufferParsed[index]);
            index += 2;
        }
        indexCommand++;
    } // to fix split with pipe
    // printCommand(command);
    return command;
}
