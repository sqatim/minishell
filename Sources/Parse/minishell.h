/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:26:24 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/17 14:15:43 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
#include <fcntl.h>

#define BUFFER_SIZE 2000

# define PIPE		"|" 
# define NWLN		"\n"
# define RIEN		"RIEN"
# define REDI_LIM	"<"
# define HERDOC 	"<<"
# define REDI_LIS 	">"
# define DOUBLE_LIS	">>" 



typedef struct s_global
{
	int exit;
} t_global;

extern t_global g_global;

typedef struct s_env
{
	char *name;
	char *value;
	char *content;
	int display;
	struct s_env *next;
	struct s_env *prev;
} t_env;

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
	char				**command;
	t_redirection		*redirections;
	struct s_command	*next;
}	t_command;

typedef struct s_parse{
	char			**command_arg;
	int				len;
	t_token			*token;
	t_command		*cmd;
	t_redirection	*redirections;
}	t_parse;

// typedef struct s_env
// {
// 	char			*name;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;

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
char	*ft_strjoin(char *s1, char *s2);
int		ft_strcmp(char *str, char *ptr);
char	*ft_substr(const char *s, unsigned int start, size_t len);

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
t_token	*ft_norm_word_h(t_token *ptr, t_main *m_main, int *index, char *line);
t_token	*ft_norm_quots_h(t_token *ptr, t_main *m_main, int *index, char *line);
t_token	*ft_norm_word(t_token *ptr, t_main *m_main, int *index, char *line);
t_token	*ft_norm_quots(t_token *ptr, t_main *m_main, int *index, char *line);
t_token	*ft_norm_word_h(t_token *ptr, t_main *m_main, int *index, char *line);
t_token	*ft_norm_quots_h(t_token *ptr, t_main *m_main, int *index, char *line);
t_token	*ft_check_norm(t_token *ptr, t_main *m_main, int *index, char *line);
void	ft_free(t_main *m_main);

/****************quots****************/

char	*check_quotes(int *indice, char *line, t_main *m_main);
char	*between_quots(char *line, int *indice, char type, t_main *main);
int		word_len_quotes(int i, char *line, char type);
int		find_quotes(char *line, int *indice, char type);
char	*quotes_after_quotes(char *line, int *indice, char type);
char	*check_quotes_h(int *indice, char *line, t_main *m_main);
char	*between_quots_h(char *line, int *indice, char type, t_main *main);

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
void	ft_check_dollar_h(char **token, int *index, int *flag_dollar);
void	take_token_h(int flag, char **token, char *value, char *name);
void	after_dollar_h(t_env *env, char **token, char *name, int flag);
void	expand_after_dollar_h(char **token, t_env *env);


/****************syntax error****************/

int	ft_check_syntax(t_main *main);
int		ft_check(t_token *head);
int		ft_error_redi(t_token *head);

/****************ft_malloc****************/

void    *ft_malloc(size_t type, size_t size);
void	add_to_trash(void *ptr, t_trash **stack_trash);


/****************parse****************/

t_command		*ft_parse(t_token *token);
void			initialize_parse(t_parse *parse, t_token *tokens_list);
int				len_arg(char **cmd_arg);
void			get_command_arg(t_parse *var);
int				ft_check_word(char *token);
int				ft_norm_redi(char *value);

#endif