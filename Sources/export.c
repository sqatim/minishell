/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:25:08 by kernel            #+#    #+#             */
/*   Updated: 2022/12/09 19:26:37 by sqatim           ###   ########.fr       */
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

void printEnvWithExport(t_execution *execStruct,t_env *env)
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
        ft_putstr_fd(value, 1);
        ft_putendl_fd("\"", 1);
        sortedEnv = sortedEnv->next;
    }
    freeEnv(sortedEnv);
}

char **parseExportArgument(char *argument)
{
    char **keyValue;
    int index;
    int keyIndex;

    index = 0;
    keyIndex = 0;
    while (argument[index] != '=' && argument[index])
    {
        if (!ft_isalpha(argument[index]) && argument[index] != '_')
        {
            ft_putstr_fd("export: `", 2);
            ft_putstr_fd(argument, 2);
            ft_putendl_fd("': not a valid identifier", 2);
            return (NULL);
        }
        index++;
    }
    keyValue = (char **)calloc(3, sizeof(char *));
    if (argument[index] == '=')
    {
        keyValue[0] = ft_substr(argument, 0, index);
        keyValue[1] = ft_substr(argument, index + 1, ft_strlen(argument));
    }
    else
        keyValue[0] = ft_substr(argument, 0, ft_strlen(argument));
    return (keyValue);
}

int checkExportArgument(char *argument)
{
    return (0);
}

char *joinExportKeyValue(char **keyValue)
{
    char *joined;

    joined = ft_strjoin(keyValue[0], "=");
    joined = ft_strjoin(joined, keyValue[1]);
    return joined;
}

t_env *handleExport(t_execution *execStruct, t_env *env, char **argument)
{
    t_env *tempEnv;
    char **keyValue;
    char *keyValueJoined;
    int index;

    tempEnv = env;
    index = 1;
    while (argument[index])
    {
        keyValue = parseExportArgument(argument[index]);
        // to handle ---------------
        if (keyValue && !keyValue[1])
        {
            // printf("Just for test: %s\n", getenv(keyValue[0]));
        }
        else if (keyValue && !keyValue[2])
        {
            env = executeUnset(execStruct, env, keyValue[0]);
            keyValueJoined = joinExportKeyValue(keyValue);
            env = addEnvNode(env, keyValueJoined, 1);
            freeString(keyValueJoined);
            freeArrayTwoDimension(keyValue);
        }
        index++;
    }
    return env;
}