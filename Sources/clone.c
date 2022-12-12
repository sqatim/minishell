/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:31:18 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/12 17:59:50 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

char **cloneCommandWords(char **str)
{
    int index;
    char **new;

    index = 0;
    while (str[index])
    {
        index++;
    }
    new = ft_calloc(++index, sizeof(char *));
    index = 0;
    while (str[index])
    {
        new[index] = ft_strdup(str[index]);
        index++;
    }
    return new;
}

static t_redirection *createRedirectionNode(t_redirection *head, t_redirection *source)
{
    t_redirection *tmp = head;
    t_redirection *new;

    new = ft_calloc(1, sizeof(t_redirection));
    new->next = NULL;
    new->type = ft_strdup(source->type);
    new->f_name = ft_strdup(source->f_name);
    if (!head)
        return new;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return head;
}

t_redirection *cloneCommandRedirections(t_redirection *source)
{
    t_redirection *new;
    t_redirection *tmp;

    tmp = source;
    new = NULL;
    while (tmp)
    {
        new = createRedirectionNode(new, tmp);
        tmp = tmp->next;
    }
    return new;
}

t_command *cloneNode(t_command *source)
{
    t_command *new;
    int index;

    index = 0;
    new = ft_calloc(1, sizeof(t_command));
    new->word_cmd = cloneCommandWords(source->word_cmd);
    new->redirections = cloneCommandRedirections(source->redirections);
    return new;
}