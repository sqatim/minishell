/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:07:22 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/19 01:45:17 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	here_document_redirection(char *filename, t_env *env)
{
	int		fd;
	char	*path;

	path = ft_strjoin("/tmp/", filename);
	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0777);
	write_in_file(env, filename, fd);
	free(path);
	close(fd);
}

int	check_input_redirection(t_redirection *redirections, int *check)
{
	t_redirection	*tmp;
	int				fd;

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

void	create_here_doc_files(t_env *env, t_redirection *redirections)
{
	t_redirection	*tmp;

	signal(SIGINT, handle_here_doc_signal);
	tmp = redirections;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "<<"))
			here_document_redirection(tmp->f_name, env);
		tmp = tmp->next;
	}
	exit(0);
}

void	here_doc_sig_int(int sig)
{
	if (sig == SIGINT)
		g_global.here_doc = 1;
}

void	handle_redirection(t_env *env, t_redirection *redirections, \
						int *check)
{
	t_redirection	*tmp;
	int				pid;

	g_global.here_doc = 0;
	g_global.forkFlag = 1;
	signal(SIGINT, here_doc_sig_int);
	pid = fork();
	if (pid == 0)
		create_here_doc_files(env, redirections);
	wait(NULL);
	signal(SIGINT, handle_ctrl_c);
	g_global.forkFlag = 0;
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
