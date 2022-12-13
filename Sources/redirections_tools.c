/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:29:37 by sqatim            #+#    #+#             */
/*   Updated: 2022/12/13 17:42:05 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_redirection *addNewRedirection(t_redirection *redirectionsHead, t_redirection *currentRedirection)
{
    t_redirection *tmp;
    t_redirection *new;

    new = ft_calloc(1, sizeof(t_redirection));
    new->f_name = ft_strdup(currentRedirection->f_name);
    new->type = ft_strdup(currentRedirection->type);
    new->next = NULL;
    if (!redirectionsHead)
        return new;
    tmp = redirectionsHead;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return redirectionsHead;
}

int redirectionsLen(t_redirection *redirection)
{
    t_redirection *tmp;
    int index;

    index = 0;
    tmp = redirection;
    while (tmp)
    {
        tmp = tmp->next;
        index++;
    }
    return index;
}

int checkRedirection(t_redirection *redirection, t_redirection *current)
{
    t_redirection *tmp;

    tmp = redirection;
    if (!tmp)
        return 1;
    else if ((!ft_strcmp(tmp->type, ">>") || !ft_strcmp(tmp->type, ">")) &&
             (ft_strcmp(current->type, ">>") && ft_strcmp(current->type, ">")))
        return 1;
    else if ((!ft_strcmp(tmp->type, "<") || !ft_strcmp(tmp->type, "<<")) &&
             (ft_strcmp(current->type, "<") && ft_strcmp(current->type, "<<")))
        return 1;
    return (0);
}

t_redirection *setupTheLastRedirections(t_redirection *redirectionsHead, t_redirection *currentRedirection)
{
    t_redirection *tmp;
    t_redirection *new;
    tmp = currentRedirection;
    if (!tmp)
        return NULL;
    new = setupTheLastRedirections(new, tmp->next);
    if (redirectionsLen(new) < 2 && checkRedirection(new, tmp))
        new = addNewRedirection(new, tmp);
    return new;
}

t_redirection *checkTypeOfRedirection(t_redirection *redirection, int type)
{
    t_redirection *next;

    if (redirection)
        next = redirection->next;
    if (redirection && type == 0)
    {
        if (!ft_strcmp(redirection->type, "<<") || !ft_strcmp(redirection->type, "<"))
            return (redirection);
        else if (next && (!ft_strcmp(next->type, "<<") || !ft_strcmp(next->type, "<")))
            return (next);
    }
    if (redirection && type == 1)
    {
        if (!ft_strcmp(redirection->type, ">>") || !ft_strcmp(redirection->type, ">"))
            return (redirection);
        else if (next && (!ft_strcmp(next->type, ">>") && !ft_strcmp(next->type, ">")))
            return (next);
    }
    return (NULL);
}