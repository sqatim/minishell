/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:41:04 by kernel            #+#    #+#             */
/*   Updated: 2022/12/22 15:44:51 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void freeArrayTwoDimension(char **array)
{
    int index;

    index = 0;
    if (array)
    {
        while (array[index])
        {
            free(array[index]);
            array[index] = NULL;
            index++;
        }
        free(array);
    }
}

void freeString(char *str)
{
    free(str);
    str = NULL;
}

void freeRedirection(t_redirection **redirection)
{
    if (!*redirection)
        return;
    freeRedirection(&(*redirection)->next);
    free((*redirection)->f_name);
    free((*redirection)->type);
    (*redirection)->f_name = NULL;
    (*redirection)->type = NULL;
    free(*redirection);
    *redirection = NULL;
}

void freeEnv(t_env *env)
{
    if (!env)
        return;
    freeEnv(env->next);
    free(env->content);
    env->content = NULL;
    free(env);
    env = NULL;
}

void freeCommand(t_command **command)
{
    if (!*command)
        return;
    freeCommand(&((*command)->next));
    freeArrayTwoDimension((*command)->command);
    freeRedirection(&(*command)->redirections);
    free(*command);
    *command = NULL;
}

void freeExecutionStruct(t_execution *execStruct)
{
    if (execStruct)
    {
        if (execStruct->redirectionsSorted)
            freeRedirection(&execStruct->redirectionsSorted);
        if (execStruct->command)
            freeCommand(&execStruct->command);
        if (execStruct->env)
            freeEnv(execStruct->env);
        free(execStruct);
    }
}

void freeEnvNodeContent(t_env *node)
{
    if(node->content)
    {
        free(node->content);
        node->content = NULL;
    }
    if(node->name)
    {
        free(node->name);
        node->name = NULL;
    }
    if(node->value)
    {
        free(node->value);
        node->value = NULL;
    }
}