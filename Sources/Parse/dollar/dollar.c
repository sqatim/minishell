/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:30:41 by oqatim            #+#    #+#             */
/*   Updated: 2023/05/21 13:21:08 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

char	*join_token_after_dollar(char **token, char *d_value)
{
	char	*str;
	char	*ptr;
	char	*result;

	str = take_to_dollar(token);
	if (d_value == NULL)
		ptr = ft_strjoin_prs(str, d_value);
	else
		ptr = ft_strjoin_free(str, d_value);
	if (d_value)
		free(d_value);
	str = take_last_token(token);
	if (*token)
		free(*token);
	result = ft_strjoin_prs(ptr, str);
	return (result);
}

void	take_token(t_main *m_main, char **token, char *value, char *name)
{
	if (m_main->flag_dollar == 1)
	{
		if (value)
			*token = join_token_after_dollar(token, ft_strdup(value));
		else
			*token = join_token_after_dollar(token, value);
	}
	else if (m_main->flag_dollar == 0)
		*token = join_token_after_dollar(token, ft_strdup(name));
}

void	after_dollar(t_main *m_main, char **token, char *name)
{
	t_env	*temp;

	temp = m_main->h_env;
	while (temp != NULL)
	{
		if (!ft_strcmp(name, temp->name))
		{
			take_token(m_main, token, temp->value, name);
			break ;
		}
		else if (temp->next == NULL && (ft_strcmp(name, temp->name)) != 0)
			take_token(m_main, token, NULL, name);
		temp = temp->next;
	}
}

int	expand_after_dollar(char **token, t_main *m_main)
{
	char	*str;
	int		len;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	len = len_dollar_name(token);
	str = malloc(sizeof(char) * (len + 1));
	while ((*token)[i] != '\0' && flag == 0)
	{
		if ((*token)[i] == '$')
		{
			ft_check_dollar(token, &i, m_main);
			take_after_dollar(token, &i, &str);
			flag = 1;
			break ;
		}
		i++;
	}
	after_dollar(m_main, token, str);
	if (str)
		free(str);
	return (0);
}

int	search_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] == '\0')
			return (0);
		else if (str[i] == '$' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}
