/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:07:22 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/18 21:45:50 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void write_in_file(t_env *env, char *path, char *filename, int fd)
{
	int len;
	char *buffer;
	char *ptr_to_be_freed;

	while (1)
	{
		buffer = readline("> ");
		if (!ft_strcmp(buffer, filename) || !buffer)
			break;
		ptr_to_be_freed = buffer;
		buffer = ft_strjoin(buffer, "\n");
		free(ptr_to_be_freed);
		while (search_dollar(buffer) == 1)
			expand_after_dollar_h(&buffer, env);
		len = ft_strlen(buffer);
		write(fd, buffer, len);
        free(buffer);
	}
}

void test(int sig)
{
	if(sig == SIGINT)
		g_global.here_doc = 1;
}
void here_document_redirection(char *filename, t_env *env)
{
	int fd;
	char *path;
	int len;
	int pid;

	path = ft_strjoin("/tmp/", filename);
	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0777);
	g_global.here_doc = 0;
	signal(SIGINT, SIG_IGN);
	g_global.forkFlag = 1;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		write_in_file(env, path, filename, fd);
		exit(0);
	}
    free(path);
	signal(SIGINT, test);
	wait(NULL);
	close(fd);
	g_global.forkFlag = 0;
	signal(SIGINT, handle_ctrl_c);
}

void ouput_trunc_redirection(char *filename)
{
	int fd;

	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	close(fd);
}

void output_append_redirection(char *filename)
{
	int fd;

	fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0777);
	close(fd);
}

int check_input_redirection(t_redirection *redirections, int *check)
{
	t_redirection *tmp;
	int fd;

	tmp = redirections;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "<"))
		{
			fd = open(tmp->f_name, O_RDONLY, 0777);
			if (fd == -1)
			{
				print_fd_errors(tmp->f_name);
				g_global.exit = 1;
				*check = 0;
				return (0);
			}
			close(fd);
		}
		tmp = tmp->next;
	}
	return (1);
}

void handle_redirection(t_env *env, t_redirection *redirections,
								  int *check)
{
	t_redirection *last_redirections;
	t_redirection *tmp;

	tmp = redirections;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "<<"))
			here_document_redirection(tmp->f_name, env);
		tmp = tmp->next;
	}
	if (!check_input_redirection(redirections, check))
		return ;
	tmp = redirections;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, ">>"))
			output_append_redirection(tmp->f_name);
		else if (!ft_strcmp(tmp->type, ">"))
			ouput_trunc_redirection(tmp->f_name);
		tmp = tmp->next;
	}
}
