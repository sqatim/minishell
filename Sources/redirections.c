/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:07:22 by sqatim            #+#    #+#             */
/*   Updated: 2023/01/17 19:08:43 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/minishell.h"

void	here_document_redirection(char *filename, t_env *env)
{
	int		fd;
	char	*path;
	char	*buffer;
	char	*delimiter;
	int		len;

	buffer = ft_calloc(BUFFER_SIZE, 1);
	path = ft_strjoin("/tmp/", filename);
	delimiter = ft_strjoin(filename, "\n");
	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0777);
	g_global.here_doc = 1;
	while (ft_strcmp(buffer, delimiter) != 0)
	{
		len = read(0, buffer, BUFFER_SIZE);
		buffer[len] = '\0';
		if (!ft_strcmp(buffer, delimiter))
			break ;
		while (search_dollar(buffer) == 1)
			expand_after_dollar_h(&buffer, env);
		len = ft_strlen(buffer);
		if (ft_strcmp(buffer, delimiter) != 0)
			write(fd, buffer, len);
	}
	g_global.here_doc = 0;
	free_here_document_redirection(&buffer, &path, &delimiter, fd);
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

t_redirection	*handle_redirection(t_env *env, t_redirection *redirections, \
								int *check)
{
	t_redirection	*last_redirections;
	t_redirection	*tmp;

	tmp = redirections;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "<<"))
			here_document_redirection(tmp->f_name, env);
		tmp = tmp->next;
	}
	if (!check_input_redirection(redirections, check))
		return (NULL);
	tmp = redirections;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, ">>"))
			output_append_redirection(tmp->f_name);
		else if (!ft_strcmp(tmp->type, ">"))
			ouput_trunc_redirection(tmp->f_name);
		tmp = tmp->next;
	}
	last_redirections = setup_the_last_redirections(redirections);
	return (last_redirections);
}
