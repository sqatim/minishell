/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:16:29 by kernel            #+#    #+#             */
/*   Updated: 2022/12/22 16:14:05 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

t_env *assignEnvNode(t_env *node, char *key, char *value, char *keyValue)
{
    node->name = ft_strdup(key);
    node->value = ft_strdup(value);
    node->content = ft_strdup(keyValue);
    return (node);
}

t_env *handleShellLevel(t_env *env)
{
    t_env *node;
    int type;
    int number;
    char *itoaNumber;
    char *tmp;

    node = ft_getEnvNode(env, "SHLVL");
    if (!node)
        env = addEnvNode(env, "SHLVL=1", 1);
    else
    {
        type = checkShellLvlValue(node->value);
        if (!type)
        {
            freeEnvNodeContent(node);
            node = assignEnvNode(node, "SHLVL", "1", "SHLVL=1");
        }
        else
        {
            number = ft_atoi(node->value);
            freeEnvNodeContent(node);
            if (number >= 0 && number <= 998)
            {
                itoaNumber = ft_itoa(++number);
                tmp = itoaNumber;
                itoaNumber = ft_strjoin("SHLVL=", itoaNumber);
                node = assignEnvNode(node, "SHLVL", tmp, itoaNumber);
                free(itoaNumber);
                free(tmp);
            }
            else if (number > 998)
                node = assignEnvNode(node, "SHLVL", "", "SHLVL=");
            else if (number < 0)
                node = assignEnvNode(node, "SHLVL", "0", "SHLVL=0");
            
        }
    }
    return env;
}

t_execution *executionInitialization(char **envp)
{
    t_execution *execStruct;

    execStruct = ft_calloc(1, sizeof(t_execution));
    if (!execStruct)
        exit(1);
    execStruct->env = setupEnv(envp);
    execStruct->env = handleShellLevel(execStruct->env);
    execStruct->status = 0;
    execStruct->command = NULL;
    execStruct->redirectionsSorted = NULL;
    execStruct->path = NULL;
    return execStruct;
}

t_env *initEnv(t_env *new, char *content, int display)
{
    int index;

    index = 0;
    if (display == 0)
    {
        new->name = ft_strdup(content);
        new->value = NULL;
    }
    else
    {
        while (content[index] != '=')
            index++;
        new->name = ft_substr(content, 0, index);
        new->value = ft_substr(content, ++index, ft_strlen(content));
    }
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