/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:58:35 by kernel            #+#    #+#             */
/*   Updated: 2022/11/26 00:03:31 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 2000

typedef struct s_env
{
    char *content;
    struct s_env *next;
    struct s_env *prev;
} t_env;

typedef struct s_execution
{
    t_env *env;
} t_execution;

void checkCommand(char **cmdLine, t_execution *execStruct);
void minishellLoop(t_execution *execStruct);
t_env *setupEnv(char **envp);
t_execution *executionInitialization(char **envp);

// builtins
void executeEnv(t_env *env);
t_env *executeUnset(t_env *env, char *argument);
t_env *executeExport(t_env *env, char **argument);
t_env *addEnvNode(t_env *head, char *content);
void executePwd();

// Export
void printEnvWithExport(t_env *env);
t_env *sortEnv(t_env *env);
t_env *handleExport(t_env *env, char **argument);

// free
void freeArrayTwoDimension(char **array);
void freeString(char *str);
void freeEnv(t_env *env);

// To delete;
char **parseCommand(char *cmdLine);
#endif