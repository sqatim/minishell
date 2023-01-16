/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_hair.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:25:20 by oussama           #+#    #+#             */
/*   Updated: 2023/01/16 14:23:15 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

void ft_check_dollar_h(char **token, int *index, int *flag_dollar)
{
	int count;
	int i;

	i = *index;
	count = 0;
	while ((*token)[i++] == '$')
		count++;
	if (count % 2 == 0)
		*flag_dollar = 0;
	else
		*flag_dollar = 1;
}

void take_token_h(int flag, char **token, char *value, char *name)
{
	if (flag == 1)
	{
		if (value)
			*token = join_token_after_dollar(token, ft_strdup(value));
		else
			*token = join_token_after_dollar(token, value);
	}
	else if (flag == 0)
		*token = join_token_after_dollar(token, name);
}

void after_dollar_h(t_env *env, char **token, char *name, int flag)
{
	while (env != NULL)

	{
		if (!ft_strcmp(name, env->name))
		{
			take_token_h(flag, token, env->value, name);
			break;
		}
		else if (env->next == NULL && (ft_strcmp(name, env->name)) != 0)
			take_token_h(flag, token, NULL, name);
		env = env->next;
	}
}

int expand_after_dollar_h(char **token, t_env *env)
{
	char *str;
	int len;
	int i;
	int flag;
	int flag_dollar;

	i = 0;
	flag = 0;
	len = len_dollar_name(token);
	str = malloc(sizeof(char) * (len + 1));
	while ((*token)[i] != '\0' && flag == 0)
	{
		if ((*token)[i] == '$')
		{
			ft_check_dollar_h(token, &i, &flag_dollar);
			take_after_dollar(token, &i, &str);
			flag = 1;
			break;
		}
		i++;
	}
	after_dollar_h(env, token, str, flag_dollar);
	if (str)
		free(str);
	return (0);
}