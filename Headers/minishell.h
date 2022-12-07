/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:26:24 by oqatim            #+#    #+#             */
/*   Updated: 2022/12/07 14:54:57 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 

#include "../Libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

# define PIPE		"|" 
# define NWLN		"\n"
# define RIEN		"RIEN"
# define REDI_LIM	"<"
# define HERDOC 	"<<"
# define REDI_LIS 	">"
# define DOUBLE_LIS	">>" 

/***************** EXECUTION *****************/

#define BUFFER_SIZE 2000
#define GREATER_THAN_MAXLONG 1
#define LESS_THAN_MINLONG 2


/***************** PARSE *****************/

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
	char 			*content;
	int 			display;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_main{
	t_command		*cmd;
	t_token			*list;
	t_env			*h_env;
	char			*line;
	int				flag_dollar;
}	t_main;



/***************** EXECUTION *****************/

typedef struct s_execution
{
    t_env *env;
    int status;
} t_execution;


/***************** PARSE *****************/


/****************libft_utils****************/

int		get_lenght(char *ln, char c);
char	*ft_strjoin_prs(char *s1, char *s2);

/****************ft_split****************/

char	**ft_split_prs(char const *s, char c);
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


int startParse(t_env *env);


/***********************Execution ***********************/

void checkCommand(char **cmdLine, t_execution *execStruct);
void minishellLoop(t_execution *execStruct);
t_env *setupEnv(char **envp);
t_execution *executionInitialization(char **envp);

// builtins
void executeEnv(t_env *env);
t_env *executeUnset(t_env *env, char *argument);
t_env *executeExport(t_env *env, char **argument);
t_env *addEnvNode(t_env *head, char *content, int display);
void executePwd();
void executeCd(t_env *env, char **argument);
void executeEcho(char **argument);
void executeExit(char **argument);

// builtins__tools
int handleNewLineInEcho(char **argument, int *indexOne);
void handleExitCases(int type, char **argument);

// Export
void printEnvWithExport(t_env *env);
t_env *sortEnv(t_env *env);
t_env *handleExport(t_env *env, char **argument);

// cd
void changeDirectory(t_env *env, char *path);
void changeDirectoryWithArgument(char *path);

// free
void freeArrayTwoDimension(char **array);
void freeString(char *str);
void freeEnv(t_env *env);

// tools
char *ft_getEnv(t_env *env, char *key);
int checkExitArgumentType(char *argument);

// other
// char	*ft_lltoa(long long n);
unsigned long long ft_atoull(const char *str);
int ft_strcmp(const char *s1, const char *s2);

// print
void printExitError(int type, char *argument);
void printError(char *cmd);

// noBuiltins;
void handleNoBuiltins(t_execution *execStruct, char **cmdLine);

// noBuiltins_tools;
char *joinPathWithCommand(char *path, char *command);

// To delete;
char **parseCommand(char *cmdLine);

#endif