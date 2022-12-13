/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:41:04 by kernel            #+#    #+#             */
/*   Updated: 2022/12/13 18:07:32 by sqatim           ###   ########.fr       */
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
    freeArrayTwoDimension((*command)->word_cmd);
    freeRedirection(&(*command)->redirections);
    free(*command);
    *command = NULL;
}