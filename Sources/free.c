/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:41:04 by kernel            #+#    #+#             */
/*   Updated: 2022/12/07 11:24:19 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void freeArrayTwoDimension(char **array)
{
    int index;

    index = 0;
    while (array[index])
    {
        free(array[index]);
        array[index] = NULL;
        index++;
    }
    free(array);
}

void freeString(char *str)
{
    free(str);
    str = NULL;
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