/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 06:25:25 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/09 13:16:49 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Headers/minishell.h"

void set_redirection(t_parse *parse, t_token *token, char *type)
{
	t_redirection *redirection;
	t_redirection *temp;

	redirection = malloc(sizeof(t_redirection));
	redirection->type = ft_strdup(type);
	redirection->f_name = ft_strdup(token->next->value);
	redirection->next = NULL;
	temp = parse->redirections;
	if (!temp)
	{
		parse->redirections = redirection;
		return;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = redirection;
}

t_command *first_node_cmd(char **command_arg, t_redirection *redirections)
{
	t_command *first_cmd;
	int size;
	int i;

	i = 0;
	first_cmd = malloc(sizeof(t_command));
	first_cmd->command = NULL;
	if (command_arg != NULL)
	{
		size = len_arg(command_arg);
		first_cmd->command = malloc(sizeof(char *) * (size + 1));
		while (command_arg[i] != NULL)
		{
			first_cmd->command[i] = ft_strdup(command_arg[i]);
			free(command_arg[i]);
			i++;
		}
		free(command_arg);
		first_cmd->command[i] = NULL;
	}
	first_cmd->redirections = redirections;
	first_cmd->next = NULL;
	return (first_cmd);
}

void addToEnd_cmd(t_command *cmd, char **command_arg, t_redirection *redirections)
{
	t_command *new_cmd;
	int size;
	int i;

	i = 0;
	new_cmd = cmd;
	while (new_cmd->next != NULL)
		new_cmd = new_cmd->next;
	new_cmd->next = malloc(sizeof(t_command));
	new_cmd->next->command = NULL;
	if (command_arg != NULL)
	{
		size = len_arg(command_arg);
		new_cmd->next->command = malloc(sizeof(char *) * (size + 1));
		while (command_arg[i] != NULL)
		{
			new_cmd->next->command[i] = ft_strdup(command_arg[i]);
			free(command_arg[i]);
			i++;
		}
		free(command_arg);
		new_cmd->next->command[i] = NULL;
	}
	new_cmd->next->redirections = redirections;
	new_cmd->next->next = NULL;
}

int take_command(t_parse *parse, int flag)
{
	if (flag == 0)
	{
		parse->cmd = first_node_cmd(parse->command_arg, parse->redirections);

		parse->command_arg = NULL;
		parse->redirections = NULL;
		flag = 1;
	}
	else
	{
		addToEnd_cmd(parse->cmd, parse->command_arg, parse->redirections);
		parse->command_arg = NULL;
		parse->redirections = NULL;
	}
	return (flag);
}

t_command *ft_parse(t_token *token)
{
	t_parse parse;
	int flag;

	flag = 0;
	initialize_parse(&parse, token);
	// printf("-------------------------------------------\n");
	while (parse.token != NULL)
	{
		// printf("%s\n", parse.token->value);
		if (ft_check_word(parse.token->value) && parse.command_arg == NULL)
			get_command_arg(&parse);
		if (!ft_strcmp(parse.token->value, PIPE) || !ft_strcmp(parse.token->value, NWLN) || parse.token->next == NULL)
			flag = take_command(&parse, flag);
		if (ft_norm_redi(parse.token->value))
		{
			set_redirection(&parse, parse.token, parse.token->value);
			parse.token = parse.token->next;
			if (parse.token->next == NULL)
				flag = take_command(&parse, flag);
		}
		parse.token = parse.token->next;
	}
	// printf("-------------------------------------------\n");

	return (parse.cmd);
}