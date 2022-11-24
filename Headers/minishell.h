/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel <kernel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 01:58:35 by kernel            #+#    #+#             */
/*   Updated: 2022/11/24 22:32:39 by kernel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../Libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# define BUFFER_SIZE 2000

typedef struct s_execution
{
    char **env;
}   t_execution;

void checkCommand(char **cmdLine, t_execution *execStruct);
void minishellLoop(t_execution *execStruct);
char **setupEnv(char **envp);
t_execution *executionInitialization();


// builtins
void executeEnv(char **env);

// To delete;
char **parseCommand(char *cmdLine);
#endif