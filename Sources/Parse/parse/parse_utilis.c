/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 06:27:06 by oqatim            #+#    #+#             */
/*   Updated: 2022/11/22 10:38:36 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_word_cmd(t_command *cmd)
{
	t_token	*token;
	int		len;

	len = 0;
	cmd->word_cmd = NULL;
	token = cmd->token;
	while (token != NULL && ft_strcmp(token->value, PIPE)
		&& ft_strcmp(token->value, NWLN))
	{
		if (ft_check_word(token->value))
			len++;
		if (ft_norm_redi(token->value))
			token = token->next;
		token = token->next;
	}
	return (len);
}

void	get_word_cmd(t_command *cmd)
{
	t_token		*token;
	int			i;
	int			len;

	i = 0;
	token = cmd->token;
	len = len_word_cmd(cmd);
	cmd->word_cmd = ft_malloc(sizeof(char *), (len + 1));
	while (token != NULL && ft_strcmp(token->value, PIPE)
		&& ft_strcmp(token->value, NWLN))
	{
		if (ft_check_word(token->value))
		{
			cmd->word_cmd[i] = ft_strdup(token->value);
			printf(" cmd->word_cmd[i]*************>|%s|\n", cmd->word_cmd[i]);
			i++;
		}
		if (ft_norm_redi(token->value))
		{
			take_redirection (cmd, token, token->value);
			token = token->next;
		}
		token = token->next;
	}
	cmd->word_cmd[i] = NULL;
}

void	initialize_cmd(t_command *cmd, t_token *token)
{
	cmd->token = token;
	cmd->redirections = NULL;
	cmd->word_cmd = NULL;
	cmd = NULL;
}
