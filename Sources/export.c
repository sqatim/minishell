/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:25:08 by kernel            #+#    #+#             */
/*   Updated: 2022/12/22 20:11:38 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;

    i = 0;
    if ((!s1 || !s2))
        return (-1);
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    if (((s1[i] == '\0' && s2[i] != '\0') || (s2[i] == '\0' && s1[i] != '\0')))
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    return (0);
}

t_env *envClone(t_env *env)
{
    t_env *tmp;
    t_env *newEnv;

    tmp = env;
    newEnv = NULL;
    while (tmp)
    {
        newEnv = addEnvNode(newEnv, tmp->content, tmp->display);
        tmp = tmp->next;
    }
    return (newEnv);
}

t_env *sortEnv(t_env *env)
{
    t_env *firstTmp;
    t_env *secondTmp;
    t_env *envExport;
    char *tmp;

    envExport = envClone(env);
    if (envExport)
    {
        firstTmp = envExport;
        secondTmp = envExport;
        while (firstTmp->next)
        {
            secondTmp = firstTmp->next;
            while (secondTmp)
            {
                if (ft_strcmp(secondTmp->content, firstTmp->content) < 0)
                {
                    tmp = firstTmp->content;
                    firstTmp->content = secondTmp->content;
                    secondTmp->content = tmp;
                }
                secondTmp = secondTmp->next;
            }
            firstTmp = firstTmp->next;
        }
    }
    return envExport;
}

void printValueOfExport(char *value)
{
    int index;

    index = 0;
    while (value[index])
    {
        if (value[index] == '"')
            ft_putchar_fd('\\', 1);
        ft_putchar_fd(value[index], 1);
        index++;
    }
}

void printEnvWithExport(t_execution *execStruct, t_env *env)
{
    t_env *sortedEnv;
    int index;
    char *key;
    char *value;

    sortedEnv = sortEnv(env);
    while (sortedEnv)
    {
        index = 0;
        while (sortedEnv->content[index] != '=')
            index++;
        key = ft_substr(sortedEnv->content, 0, ++index);
        value = ft_substr(sortedEnv->content, index, ft_strlen(sortedEnv->content));

        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(key, 1);
        ft_putstr_fd("\"", 1);
        printValueOfExport(value);
        ft_putendl_fd("\"", 1);
        sortedEnv = sortedEnv->next;
    }
    freeEnv(sortedEnv);
}

char **parseExportArgument(char *argument)
{
    char **keyValue;
    int index;

    index = 0;
    if (!argument[index] || ft_isdigit(argument[index]))
        return printExportError(argument);
    while (argument[index] != '=' && argument[index])
    {
        if (argument[index] == '+' && argument[index + 1] == '=')
            break;
        if (!ft_isalnum(argument[index]) && argument[index] != '_')
            return printExportError(argument);
        index++;
    }
    keyValue = (char **)calloc(4, sizeof(char *));
    if (argument[index] == '=' || (argument[index] == '+' && argument[index + 1] == '='))
    {
        keyValue[0] = ft_substr(argument, 0, index);
        if (argument[index] == '=')
        {
            keyValue[1] = ft_strdup("=");
            keyValue[2] = ft_substr(argument, index + 1, ft_strlen(argument));
        }
        else
        {
            keyValue[1] = ft_strdup("+=");
            keyValue[2] = ft_substr(argument, index + 2, ft_strlen(argument));
        }
    }
    else
        keyValue[0] = ft_substr(argument, 0, ft_strlen(argument));
    return (keyValue);
}

char *joinExportKeyValue(char **keyValue, char *oldValue)
{
    char *joined;
    char *oldWithNew;

    if (!ft_strcmp(keyValue[1], "+="))
    {
        joined = ft_strjoin(keyValue[0], "=");
        if (oldValue)
            oldWithNew = ft_strjoin(oldValue, keyValue[2]);
        else
            oldWithNew = ft_strjoin("", keyValue[2]);
        joined = ft_strjoin(joined, oldWithNew);
    }
    else
    {
        joined = ft_strjoin(keyValue[0], "=");
        joined = ft_strjoin(joined, keyValue[2]);
    }
    return joined;
}

t_env *handleExport(t_execution *execStruct, t_env *env, char **argument)
{
    t_env *tempEnv;
    char **keyValue;
    char *keyValueJoined;
    int index;
    char *oldValue;
    int test = 0;
    

    tempEnv = env;
    index = 1;
    while (argument[index])
    {
        keyValue = parseExportArgument(argument[index]);
        if (keyValue && !keyValue[1])
        {
            if (!ft_getEnv(env, keyValue[0]))
                env = addEnvNode(env, keyValue[0], 0);
        }
        else if (keyValue && !keyValue[3])
        {
            oldValue = ft_getEnv(env, keyValue[0]);
            if(oldValue)
                oldValue = ft_strdup(oldValue);
            env = executeUnset(execStruct, env, keyValue[0]);
            keyValueJoined = joinExportKeyValue(keyValue, oldValue);
            env = addEnvNode(env, keyValueJoined, 1);
            freeString(keyValueJoined);
            freeArrayTwoDimension(keyValue);
        }
        index++;
    }
    return env;
}