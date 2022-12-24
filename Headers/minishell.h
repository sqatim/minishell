/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samirqatim <samirqatim@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:26:24 by oqatim            #+#    #+#             */
/*   Updated: 2022/12/24 18:15:54 by samirqatim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../Libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

#define PIPE "|"
#define NWLN "\n"
#define RIEN "RIEN"
#define REDI_LIM "<"
#define HERDOC "<<"
#define REDI_LIS ">"
#define DOUBLE_LIS ">>"

/***************** EXECUTION *****************/

#define BUFFER_SIZE 2000
#define GREATER_THAN_MAXLONG 1
#define LESS_THAN_MINLONG 2
#define NON_BUILTIN 0
#define BUILTIN 1
#define TRUE 1
#define FALSE 0

/******************* GLOBAL *******************/

typedef struct s_global
{
	int forkFlag;
	int exit;

} t_global;

extern t_global g_global;
/***************** PARSE *****************/

typedef struct s_trash
{
	void *ptr;
	struct s_trash *next;
} t_trash;

typedef struct s_token
{
	char *value;
	struct s_token *next;
} t_token;

typedef struct s_redirection
{
	char *f_name;
	char *type;
	struct s_redirection *next;
} t_redirection;

typedef struct s_command
{
	char **command;
	t_redirection *redirections;
	struct s_command *next;
} t_command;

typedef struct s_parse
{
	char **command_arg;
	int len;
	t_token *token;
	t_command *cmd;
	t_redirection *redirections;
} t_parse;

typedef struct s_env
{
	char *name;
	char *value;
	char *content;
	int display;
	struct s_env *next;
	struct s_env *prev;
} t_env;

typedef struct s_main
{
	t_command *cmd;
	t_token *list;
	t_env *h_env;
	char *line;
	int flag_dollar;
} t_main;

/***************** EXECUTION *****************/

typedef struct s_context
{
	int fd[2];	  // For stdin / stdout
	int fd_close; // close fd if it's not -1
} t_context;

typedef struct s_pipe
{
	t_context left_context;
	t_context right_context;
	t_command *left_node;
	t_command *right_node;

} t_pipe;

typedef struct s_export
{
	char **key_value;
	char *key_value_joined;
	int index;
	char *old_value;
	int status;

} t_export;

typedef struct s_execution
{
	t_redirection *redirections_sorted;
	t_env *env;
	t_command *command;
	int status;
	char *path;
} t_execution;

/***************** PARSE *****************/

/****************libft_utils****************/

int get_lenght(char *ln, char c);
char *ft_strjoin_prs(char *s1, char *s2);

/****************ft_split****************/

char **ft_split(char const *s, char c);
size_t ft_strlen(const char *s);

/****************env****************/

t_env *get_env(char **env);

/****************lexer****************/

t_token *creat_first_node(t_token *head);
t_token *ft_lexer(t_token *head, t_main *m_main, char *line);
t_token *get_token_word(t_token *ptr, char *line, int *index, t_main *m_main);
char *get_word(char *line, int *index);
t_token *add_to_end_lexe(t_token *head, char *token);
t_token *add_PIPE_node(t_token *ptr, char *line, int i);
t_token *add_lim_rederi_node(t_token *ptr, char *line, int *index);
t_token *add_lis_rederi_node(t_token *ptr, char *line, int *index);
t_token *get_different_token(t_token *ptr, char *line, int *index);
t_command *startParse(t_env *env, char *buffer);

/****************quots****************/

char *check_quotes(int *indice, char *line, t_main *m_main);
char *between_quots(char *line, int *indice, char type, t_main *main);
int word_len_quotes(int i, char *line, char type);
int find_quotes(char *line, int *indice, char type);
char *quotes_after_quotes(char *line, int *indice, char type);

/****************dollar****************/

int expand_after_dollar(char **token, t_main *m_main);
void after_dollar(t_main *m_main, char **token, char *name);
void take_token(t_main *m_main, char **token, char *value, char *name);
char *join_token_after_dollar(char **token, char *d_value);
int search_dollar(char *str);
void take_after_dollar(char **token, int *index, char **name);
void ft_check_dollar(char **token, int *index, t_main *m_main);
int len_dollar_name(char **token);
int alpha_numeric(char c);
char *last_part(char **token, int *index);
char *take_last_part(char **token, int *i);
char *take_last_token(char **token);

/****************syntax error****************/

void ft_check_syntax(t_token *head);
int ft_check(t_token *head);
int ft_error_redi(t_token *head);

/****************ft_malloc****************/

void *ft_malloc(size_t type, size_t size);
void add_to_trash(void *ptr, t_trash **stack_trash);

/****************parse****************/

t_command *ft_parse(t_token *token);
void initialize_parse(t_parse *parse, t_token *tokens_list);
int len_arg(char **cmd_arg);
void get_command_arg(t_parse *var);
int ft_check_word(char *token);
int ft_norm_redi(char *value);

/***********************Execution ***********************/

int check_command(t_execution *exec_struct, t_command *command, t_context context);
int check_type_of_command(char *str);
void minishell_loop(t_execution *exec_struct);
t_env *setup_env(char **envp);
t_execution *execution_initialization(char **envp);
int check_shell_lvl_value(char *argument);

// builtins
void execute_env(t_env *env);
t_env *execute_unset(t_env *env, char *argument);
t_env *execute_export(t_env *env, char **argument);
t_env *add_env_node(t_env *head, char *content, int display);
void execute_pwd(t_execution *exec_struct);
void execute_cd(t_execution *exec_struct, t_env *env, char **argument);
void execute_echo(char **argument);
void execute_exit(t_execution *exec_struct, char **argument);
void handle_builtin_command(t_execution *exec_struct, t_command *command, t_context context);

// builtins__tools
int handle_new_line_in_echo(char **argument, int *index_one);
void handle_exit_cases(t_execution *exec_struct,int type, char **argument);
void ft_exit(t_execution *exec_struct, int status);

// Export
void print_env_with_export(t_env *env);
t_env *sort_env(t_env *env);
t_env *handle_export(t_env *env, char **argument);

// cd
t_env *change_directory(t_execution *exec_struct, t_env *env, char *path);

// free
void free_array_two_dimension(char **array);
void free_string(char *str);
void free_env(t_env *env);
void free_redirection(t_redirection **redirection);
void free_command(t_command **command);
void free_execution_struct(t_execution *exec_struct);
void free_env_node_content(t_env *node);

// tools
char *ft_get_env(t_env *env, char *key);
t_env *ft_get_env_node(t_env *env, char *key);
int check_exit_argument_type(char *argument);

// other
unsigned long long ft_atoull(const char *str);
int ft_strcmp(const char *s1, const char *s2);

// print
void print_exit_error(t_execution *exec_struct,int type, char *argument);
void print_error(char *cmd);
char **print_export_error(char *key, int *status);

// noBuiltins;
void handle_no_builtins(t_execution *exec_struct, char **cmdLine, t_context context);

// noBuiltins_tools;
char *join_path_with_command(char *path, char *command);
char **convert_env_to_array(t_env *env);

// signalHandler
void signalHandler();

// redirections
t_redirection *handle_redirection(t_redirection *redirections);
t_redirection *setup_the_last_redirections(t_redirection *current_redirection);
void here_document_redirection(char *filename);
void output_append_redirection(char *filename);
void ouput_trunc_redirection(char *filename);
t_redirection *check_type_of_redirection(t_redirection *redirection, int type);

// exec
void start_execution(t_execution *exec_struct, t_command *command);
int execCommandOfNode(t_execution *exec_struct, t_command *command, t_context context);
int execRedirection(t_execution *exec_struct, t_context context);
int exec_input_redirection(t_redirection *input);
int exec_output_redirection(t_redirection *output);

// clone
t_command *clone_node(t_command *source);
char **clone_command_words(char **str);

// To delete;
t_command *customizeMyParse(char *buffer);
void printRedirection(t_redirection *redirections);

#endif