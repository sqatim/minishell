/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 06:27:06 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/18 13:15:52 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

void	len_command_arg(t_parse *parse, t_token *token)
{
	while (token != NULL && ft_strcmp(token->value, PIPE)
		&& ft_strcmp(token->value, NWLN))
	{
		if (ft_check_word(token->value))
			parse->len++;
		if (ft_norm_redi(token->value))
			token = token->next;
		token = token->next;
	}
}

void	get_command_arg(t_parse *parse)
{
	t_token	*token;
	int		i;

	i = 0;
	parse->len = 0;
	parse->command_arg = NULL;
	token = parse->token;
	len_command_arg(parse, token);
	parse->command_arg = malloc(sizeof(char *) * (parse->len + 1));
	while (i < parse->len)
	{
		if (ft_check_word(token->value))
			parse->command_arg[i++] = ft_strdup(token->value);
		if (ft_norm_redi(token->value))
			token = token->next;
		token = token->next;
	}
	parse->command_arg[i] = NULL;
}

void	initialize_parse(t_parse *parse, t_token *token)
{
	parse->token = token;
	parse->redirections = NULL;
	parse->command_arg = NULL;
	parse->cmd = NULL;
}

int	len_arg(char **cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i] != NULL)
		i++;
	return (i);
}
