/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:30:41 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/17 14:02:23 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;
	int		r;

	i = 0;
	r = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	len = get_lenght(s1, '\0') + get_lenght(s2, '\0') + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1[i])
		str[r++] = s1[i++];
	i = 0;
	while (s2[i])
		str[r++] = s2[i++];
	str[r] = 0;
	free(s1);
	// free(s2);
	return (str);
}

char *join_token_after_dollar(char **token, char *d_value)
{
	char *str;
	char *ptr;
	char *result;
	int len;
	int i;

	i = 0;
	// ptr = ft_strdup("");
	len = get_lenght((*token), '$');
	str = malloc(sizeof(char) * (len + 1));
	while ((*token)[i] != '$' && (*token)[i] != '\0')
	{
		str[i] = (*token)[i];
		i++;
	}
	str[i] = '\0';
	ptr = ft_strjoin_free(str, d_value);
	if(d_value)
		free(d_value);
	printf("str ==> %s\n",*token);
	str = take_last_token(token);
	if (*token)
		free(*token);
	result = ft_strjoin(ptr, str);
	printf("result |%s|\n",result);
	// if(str)
	// {
	// 	free(str);
	// 	str = NULL;
	// }
	// // if (ptr)
	// // {
	// // 	ptr = NULL;
	// // 	free(ptr);
	// // }
	// if (d_value)
	// {
	// 	free(d_value);
	// 	d_value = NULL;
	// }
	// puts("********************************************************************************************");
	// printf("result ==>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%s\n", result);
	// puts("********************************************************************************************");
	return (result);
}

void take_token(t_main *m_main, char **token, char *value, char *name)
{
	if (m_main->flag_dollar == 1)
	{
		if (value)
		{
			puts("waaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
			*token = join_token_after_dollar(token, ft_strdup(value));
		}
		else
			*token = join_token_after_dollar(token, value);
	}
	else if (m_main->flag_dollar == 0)
	{
		
			puts("NULL");
		*token = join_token_after_dollar(token, ft_strdup(name));
		printf("take_token => |%s|\n",*token);
	}
}

void after_dollar(t_main *m_main, char **token, char *name)
{
	t_env *temp;

	temp = m_main->h_env;
	while (temp != NULL)
	{
		if (!ft_strcmp(name, temp->name))
		{
			take_token(m_main, token, temp->value, name);
			break;
		}
		else if (temp->next == NULL && (ft_strcmp(name, temp->name)) != 0)
			take_token(m_main, token, NULL, name);
		temp = temp->next;
	}
}

int expand_after_dollar(char **token, t_main *m_main)
{
	char *str;
	int len;
	int i;
	int flag;

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
			break;
		}
		i++;
	}
	after_dollar(m_main, token, str);
	// printf("|%s|\n",token);
	if (str)
		free(str);
	return (0);
}

int search_dollar(char *str)
{
	int i;

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
