/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqatim <oqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:26:24 by oqatim            #+#    #+#             */
/*   Updated: 2023/01/19 02:37:06 by oqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# define PIPE "|"
# define NWLN "\n"
# define RIEN "RIEN"
# define REDI_LIM "<"
# define HERDOC "<<"
# define REDI_LIS ">"
# define DOUBLE_LIS ">>"

/***************** EXECUTION *****************/

# define BUFFER_SIZE 2000
# define GREATER_THAN_MAXLONG 1
# define LESS_THAN_MINLONG 2
# define NON_BUILTIN 0
# define BUILTIN 1
# define TRUE 1
# define FALSE 0

/******************* GLOBAL *******************/

typedef struct s_global
{
	int	fork_flag;
	int	exit;
	int	here_doc;
	int	error;
}			t_global;

extern t_global	g_global;
/***************** PARSE *****************/

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection
{
	char					*f_name;
	char					*type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				**command;
	t_redirection		*redirections;
	struct s_command	*next;
}	t_command;

typedef struct s_parse
{
	char			**command_arg;
	int				len;
	t_token			*token;
	t_command		*cmd;
	t_redirection	*redirections;
}	t_parse;

typedef struct s_env
{
	char			*name;
	char			*value;
	char			*content;
	int				display;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_main
{
	t_command	*cmd;
	t_token		*list;
	t_env		*h_env;
	char		*line;
	int			flag_dollar;
}	t_main;

/***************** EXECUTION *****************/

typedef struct s_context
{
	int	fd[2];
	int	fd_close;
}	t_context;

typedef struct s_pipe
{
	t_context	left_context;
	t_context	right_context;
	t_command	*left_node;
	t_command	*right_node;

}	t_pipe;

typedef struct s_export
{
	char	**key_value;
	char	*key_value_joined;
	char	*old_value;
	int		index;
	int		status;
}	t_export;

typedef struct s_execution
{
	t_redirection	*redirections_sorted;
	t_env			*env;
	t_command		*command;
	char			**env_array;
	char			*path;
	int				status;
}	t_execution;

/***************** PARSE *****************/

/****************libft_utils****************/

int					get_lenght(char *ln, char c);
char				*ft_strjoin_prs(char *s1, char *s2);

/****************ft_split****************/

char				**ft_split(char const *s, char c);
size_t				ft_strlen(const char *s);

/****************env****************/

t_env				*get_env(char **env);

/****************lexer****************/

t_token				*creat_first_node(t_token *head);
t_token				*ft_lexer(t_token *head, t_main *m_main, char *line);
t_token				*get_token_word(t_token *ptr, char *line, \
						int *index, t_main *m_main);
char				*get_word(char *line, int *index);
t_token				*add_to_end_lexe(t_token *head, char *token);
t_token				*add_PIPE_node(t_token *ptr, char *line, int i);
t_token				*add_lim_rederi_node(t_token *ptr, char *line, int *index);
t_token				*add_lis_rederi_node(t_token *ptr, char *line, int *index);
t_token				*get_different_token(t_token *ptr, char *line, int *index);
t_command			*start_parse(t_env *env, char *buffer);
t_token				*ft_norm_word(t_token *ptr, t_main *m_main, \
						int *index, char *line);
t_token				*ft_norm_quots(t_token *ptr, t_main *m_main, \
						int *index, char *line);
t_token				*ft_norm_word_h(t_token *ptr, int *index, char *line);
t_token				*ft_norm_quots_h(t_token *ptr, int *index, char *line);
t_token				*ft_check_norm(t_token *ptr, int *index, char *line);
void				ft_free(t_main *m_main);

/****************quots****************/

char				*check_quotes(int *indice, char *line, t_main *m_main);
char				*between_quots(char *line, int *indice, \
						char type, t_main *main);
int					word_len_quotes(int i, char *line, char type);
int					find_quotes(char *line, int *indice, char type);
char				*quotes_after_quotes(char *line, int *indice, char type);
char				*between_quots_h(char *line, int *indice, char type);
char				*check_quotes_h(int *indice, char *line);

/****************dollar****************/

int					expand_after_dollar(char **token, t_main *m_main);
void				after_dollar(t_main *m_main, char **token, char *name);
void				take_token(t_main *m_main, char **token, \
							char *value, char *name);
char				*join_token_after_dollar(char **token, char *d_value);
int					search_dollar(char *str);
void				take_after_dollar(char **token, int *index, char **name);
void				ft_check_dollar(char **token, int *index, t_main *m_main);
int					len_dollar_name(char **token);
int					alpha_numeric(char c);
char				*last_part(char **token, int *index);
char				*take_last_part(char **token, int *i);
char				*take_last_token(char **token);
void				ft_check_dollar_h(char **token, int *index, \
						int *flag_dollar);
void				take_token_h(int flag, char **token, char *value, \
						char *name);
void				after_dollar_h(t_env *env, char **token, \
						char *name, int flag);
void				expand_after_dollar_h(char **token, t_env *env);
char				*ft_global_exit(char **token, int *index);
int					boucle_for_dollar(char **token, int *index, int x);
char				*ft_len_dollar(int x);
char				*take_to_dollar(char **token);
char				*ft_strjoin_free(char *s1, char *s2);

/****************syntax error****************/

int					ft_check_syntax(t_main *head);
int					ft_check(t_token *head);
int					ft_error_redi(t_token *head);

/****************parse****************/

t_command			*ft_parse(t_token *token);
void				initialize_parse(t_parse *parse, t_token *tokens_list);
int					len_arg(char **cmd_arg);
void				get_command_arg(t_parse *var);
int					ft_check_word(char *token);
int					ft_norm_redi(char *value);

/***********************Execution ***********************/

int					check_command(t_execution *exec_struct, \
						t_command *command, t_context context);
int					check_type_of_command(char *str);
void				minishell_loop(t_execution *exec_struct);
t_env				*setup_env(char **envp);
t_execution			*execution_initialization(char **envp);
int					check_shell_lvl_value(char *argument);

// builtins
void				execute_env(t_env *env);
t_env				*execute_unset(t_execution *exec_struct, \
						t_env *env, char **argument);
t_env				*execute_export(t_execution *exec_struct, \
						t_env *env, char **argument);
t_env				*add_env_node(t_env *head, char *content, int display);
void				execute_pwd(t_execution *exec_struct);
void				execute_cd(t_execution *exec_struct, t_env *env, \
						char **argument);
void				execute_echo(char **argument);
void				execute_exit(t_execution *exec_struct, char **argument);
void				handle_builtin_command(t_execution *exec_struct, \
						t_command *command, t_context context, int check);
int					unset_itterator(t_env **tmp, char *tmp_argument);
t_env				*execute_unset_for_export(t_execution *exec_struct, \
						t_env *env, char *argument);

// builtins__tools
int					handle_new_line_in_echo(char **argument, int *index_one);
void				handle_exit_cases(t_execution *exec_struct, int type, \
						char **argument);
void				ft_exit(t_execution *exec_struct, int status);
char				*check_current_path(t_execution *execStruct);

// Export
void				print_env_with_export(t_env *env);
t_env				*sort_env(t_env *env);
t_env				*handle_export(t_execution *exec_struct, t_env *env, \
						char **argument);
void				print_env_with_export_second(t_env *sorted_env, \
						int index, int display);

// cd
t_env				*change_directory(t_execution *exec_struct, \
						t_env *env, char *path);

// free
void				free_array_two_dimension(char **array);
void				free_string(char *str);
void				free_env(t_env *env);
t_redirection		*free_redirection(t_redirection *redirection);
t_command			*free_command(t_command *command);
void				free_execution_struct(t_execution *exec_struct);
void				free_env_node_content(t_env *node);
void				free_export_struct(t_export *export);

// tools
char				*ft_get_env(t_env *env, char *key);
char				*ft_get_node_env_without_exception(t_env *env, char *key);
t_env				*ft_get_env_node(t_env *env, char *key);
int					check_exit_argument_type(char *argument);

// other
unsigned long long	ft_atoull(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
t_export			export_init(void);

// print
void				print_exit_error(t_execution *exec_struct, \
						int type, char *argument);
void				print_error(char *cmd);
void				print_command_not_found(char *cmd);
char				**print_export_error(char *key, int *status);
void				print_cd_error(char *path, int type);
void				print_fd_errors(char *file_name);
char				**print_unset_error(char *key, int *status);

// noBuiltins;
void				handle_no_builtins(t_execution *exec_struct, \
						char **cmdLine, t_context context, int check);

// noBuiltins_tools;
char				*join_path_with_command(char *path, char *command);
char				**convert_env_to_array(t_execution *exec_struct, \
						t_env *env);
void				change_pwd_in_env_in_case_of_error(t_execution \
						*exec_struct, t_env *env);
int					env_linked_list_len(t_env *env);
int					env_linked_list_len_with_key_value(t_env *env);

// signalHandler
void				signal_handler(void);
void				handle_ctrl_c(int signum);

// redirections
void				handle_redirection(t_env *env, \
						t_redirection *redirections, int *check);
t_redirection		*setup_the_last_redirections(t_redirection \
						*current_redirection);
void				here_document_redirection(char *filename, t_env *env);
void				output_append_redirection(char *filename);
void				ouput_trunc_redirection(char *filename);
t_redirection		*check_type_of_redirection(t_redirection *redirection, \
						int type);
int					check_input_redirection(t_redirection *redirections, \
						int *check);
void				write_in_file(t_env *env, char *filename, int fd);
void				handle_here_doc_signal(int sig);

// exec
void				start_execution(t_execution *exec_struct, \
						t_command *command);
int					exec_command_of_node(t_execution *exec_struct, \
						t_command *command, t_context context);
int					exec_redirection(t_execution *exec_struct, \
						t_context context);
int					exec_input_redirection(t_redirection *input);
int					exec_output_redirection(t_redirection *output);
t_env				*env_clone(t_env *env);
t_env				*switch_env_node(t_env *first_tmp, t_env **second_tmp);

// clone
t_command			*clone_node(t_command *source);
char				**clone_command_words(char **str);
t_redirection		*create_redirection_node(t_redirection *head, \
						t_redirection *source);

// init
t_env				*assign_env_node(t_env *node, char *key, \
						char *value, char *key_value);

#endif