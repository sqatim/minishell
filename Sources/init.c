/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:16:29 by kernel            #+#    #+#             */
/*   Updated: 2022/12/07 13:37:20 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

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

t_env *initEnv(t_env *new, char *content, int display)
{
    int index;

    index = 0;
    while (content[index] != '=')
        index++;
    new->name = ft_substr(content, 0, index);
    new->value = ft_substr(content, ++index, ft_strlen(content));
    new->content = ft_strdup(content);
    new->display = display;

    return (new);
}
t_env *addEnvNode(t_env *head, char *content, int display)
{
    t_env *tmp;
    t_env *new;
    char **keyvalue;

    new = (t_env *)calloc(1, sizeof(t_env));
    // to handle ---------
    if (!new)
        exit(1);
    new = initEnv(new, content, display);
    // new->name = keyvalue[]
    new->next = NULL;
    new->prev = NULL;
    if (!head)
        return new;
    tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
    return (head);
}