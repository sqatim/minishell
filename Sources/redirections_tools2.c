/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_tools2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:43:44 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/19 01:46:51 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	write_in_file(t_env *env, char *filename, int fd)
{
	int		len;
	char	*buffer;
	char	*ptr_to_be_freed;

	while (1)
	{
		buffer = readline("> ");
		if (!ft_strcmp(buffer, filename) || !buffer)
			break ;
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

void	ouput_trunc_redirection(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	close(fd);
}

void	output_append_redirection(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0777);
	close(fd);
}

void	handle_here_doc_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_global.here_doc = 1;
		exit(1);
	}
}
