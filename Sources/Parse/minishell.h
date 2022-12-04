/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:26:24 by oqatim            #+#    #+#             */
/*   Updated: 2022/12/04 17:05:46 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define PIPE		"|" 
# define NWLN		"\n"
# define RIEN		"RIEN"
# define REDI_LIM	"<"
# define HERDOC 	"<<"
# define REDI_LIS 	">"
# define DOUBLE_LIS	">>" 


typedef struct s_trash
{
	void			*ptr;
	struct s_trash	*next;
}	t_trash;

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection {
	char					*f_name;
	char					*type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command{
	char				**word_cmd;
	t_token				*token;
	t_redirection		*redirections;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_main{
	t_command		*cmd;
	t_token			*list;
	t_env			*h_env;
	char			*line;
	int				flag_dollar;
}	t_main;

/****************libft_utils****************/

char	*ft_strdup(char *str);
int		get_lenght(char *ln, char c);
char	*ft_strchr(char *str, char c);
char	*ft_strjoin_prs(char *s1, char *s2);
int		ft_strcmp(char *str, char *ptr);

/****************ft_split****************/

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);

/****************env****************/

t_env	*get_env(char **env);

/****************lexer****************/

t_token	*creat_first_node(t_token *head);
t_token	*ft_lexer(t_token *head, t_main *m_main, char *line);
t_token	*get_token_word(t_token *ptr, char *line, int *index, t_main *m_main);
char	*get_word(char *line, int *index);
t_token	*add_to_end_lexe(t_token *head, char *token);
t_token	*add_PIPE_node(t_token *ptr, char *line, int i);
t_token	*add_lim_rederi_node(t_token *ptr, char *line, int *index);
t_token	*add_lis_rederi_node(t_token *ptr, char *line, int *index);
t_token	*get_different_token(t_token *ptr, char *line, int *index);

/****************quots****************/

char	*check_quotes(int *indice, char *line, t_main *m_main);
char	*between_quots(char *line, int *indice, char type, t_main *main);
int		word_len_quotes(int i, char *line, char type);
int		find_quotes(char *line, int *indice, char type);
char	*quotes_after_quotes(char *line, int *indice, char type);

/****************dollar****************/

int		expand_after_dollar(char **token, t_main *m_main);
void	after_dollar(t_main *m_main, char **token, char *name);
void	take_token(t_main *m_main, char **token, char *value, char *name);
char	*join_token_after_dollar(char **token, char *d_value);
int		search_dollar(char *str);
void	take_after_dollar(char **token, int *index, char **name);
void	ft_check_dollar(char **token, int *index, t_main *m_main);
int		len_dollar_name(char **token);
int		alpha_numeric(char c);
char	*last_part(char **token, int *index);
char	*take_last_part(char **token, int *i);
char	*take_last_token(char **token);

/****************syntax error****************/

void	ft_check_syntax(t_token *head);
int		ft_check(t_token *head);
int		ft_error_redi(t_token *head);

/****************parse****************/

t_command	*ft_parse(t_command *cmd, t_token *token);
void		take_redirection(t_command *cmd, t_token *token, char *redi_type);
void		initialize_cmd(t_command *cmd, t_token *token);
void		get_word_cmd(t_command *cmd);
int			len_word_cmd(t_command *cmd);
int			ft_check_word(char *token);
int			ft_norm_redi(char *value);

/****************ft_malloc****************/

void    *ft_malloc(size_t type, size_t size);
void	add_to_trash(void *ptr, t_trash **stack_trash);

#endif