/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:16:29 by kernel            #+#    #+#             */
/*   Updated: 2022/11/28 14:23:52 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_execution *executionInitialization(char **envp)
{
    t_execution *execStruct;

    execStruct = ft_calloc(1, sizeof(t_execution));
    if (!execStruct)
        exit(1);
    execStruct->env = setupEnv(envp);
    execStruct->status = 0;
    return execStruct;
}

t_env *addEnvNode(t_env *head, char *content, int display)
{
    t_env *tmp;
    t_env *new;

    new = (t_env *)calloc(1, sizeof(t_env));
    // to handle ---------
    if (!new)
        exit(1);
    new->content = ft_strdup(content);
    new->display = display;
    new->next = NULL;
    new->prev = NULL;
    // ft_putstr_fd(new->content, 1);
    // exit(1);
    if (!head)
        return new;
    tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
    return (head);
}