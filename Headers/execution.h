/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:58:35 by kernel            #+#    #+#             */
/*   Updated: 2022/12/07 11:23:28 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "../Libft/libft.h"
#include "../Sources/Parse/../../Headers/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 2000
#define GREATER_THAN_MAXLONG 1
#define LESS_THAN_MINLONG 2

// typedef struct s_env
// {
//     char *content;
//     int display;
//     struct s_env *next;
//     struct s_env *prev;
// } t_env;

typedef struct s_execution
{
    t_env *env;
    int status;
} t_execution;

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