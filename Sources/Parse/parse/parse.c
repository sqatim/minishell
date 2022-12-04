/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 06:25:25 by oqatim            #+#    #+#             */
/*   Updated: 2022/12/03 13:39:44 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	take_redirection(t_command *cmd, t_token *token, char *redi_type)
{
	t_redirection	*redirection;
	t_redirection	*temp;

	redirection = ft_malloc(sizeof(t_redirection), 1);
	redirection->type = redi_type;
	redirection->f_name = token->next->value;
	redirection->next = NULL;
	puts("-----------------------------");
	printf("redirection->type == %s  ||  redirection->f_name == %s\n", redirection->type, redirection->f_name);
	puts("-----------------------------");
	temp = cmd->redirections;
	if (!temp)
	{
		cmd->redirections = redirection;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = redirection;
}

t_command	*ft_parse(t_command *cmd, t_token *token)
{
	int	flag;

	flag = 0;
	cmd = ft_malloc(sizeof(t_command), 1);
	initialize_cmd(cmd, token);
	while (cmd->token != NULL)
	{
		if (ft_check_word(cmd->token->value))
		{
			get_word_cmd(cmd);
			while (ft_strcmp(cmd->token->value, PIPE)
				&& ft_strcmp(cmd->token->value, NWLN)
				&& cmd->token->next != NULL)
				cmd->token = cmd->token->next;
		}
		if (ft_norm_redi(cmd->token->value))
		{	
			take_redirection(cmd, cmd->token, cmd->token->value);
			cmd->token = cmd->token->next;
		}
		// getchar();
		cmd->token = cmd->token->next;
	}
	return (cmd);
}
