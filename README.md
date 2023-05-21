# Minishell

## Introduction

Minishell is a project that involves creating a simple shell, which is a command-line interface that allows users to interact with the operating system. The purpose of this project is to teach you about processes and file descriptors, which are important concepts in computer programming.

The Minishell project requires you to create your own little bash shell using the C programming language. You will need to implement various features, such as redirections, pipes, and environment variables. Redirections allow you to redirect input or output from one command to another. Pipes allow you to connect the output of one command to the input of another command. Environment variables are variables that hold information about the environment in which your program is running.

In addition to these features, you will also need to handle various signals, such as ctrl-C and ctrl-D. These signals behave differently depending on the context in which they are used, so it's important to understand how they work in order to handle them correctly.

## Subject
+ [Minishell Subject](/Minishell_subject.pdf)

## Detailed Functions Required for the Minishell Project.
1. `main`: This function should handle user input and execute commands. It should read user input from the command line, parse the input, and execute the resulting commands.

2. `parse_input`: This function should take a string of user input and parse it into individual commands and arguments. It should handle quotes, escape characters, and whitespace properly.

3. `execute_command`: This function should execute a single command with its arguments. It should use `execve` to execute external commands, and handle built-in commands such as `cd`, `echo`, and `env` internally.

4. `handle_redirections`: This function should handle input/output redirections using the `<`, `>`, `<<`, and `>>` operators. It should open or create files as necessary, and redirect input or output as specified.

5. `handle_pipes`: This function should handle pipes using the `|` operator. It should create pipes as necessary, fork child processes to execute each command in the pipeline, and connect their input/output streams via the pipe.

6. `handle_environment_variables`: This function should handle environment variables using the `$` operator. It should expand variables such as `$PATH` to their values, or leave them unchanged if they are not defined.

7. `handle_exit_status`: This function should handle the `$?` operator, which expands to the exit status of the most recently executed foreground pipeline.

8. `handle_signals`: This function should handle signals such as ctrl-C, ctrl-D, and ctrl-\, which behave differently depending on the context in which they are used. For example, ctrl-C should interrupt a running command but not exit the shell entirely.

## Details about the Builtins Requested in the Minishell.

1. `echo`: This builtin should print its arguments to standard output, followed by a newline character. If the `-n` option is provided as the first argument, then no newline character should be printed.

2. `cd`: This builtin should change the current working directory of the shell to the directory specified by its first argument. If no argument is provided, then it should change to the home directory of the user. The path can be either absolute or relative.

3. `pwd`: This builtin should print the current working directory of the shell to standard output.

4. `export`: This builtin should add a new environment variable to the shell's environment with a name and value specified by its arguments. If no arguments are provided, then it should print all environment variables and their values to standard output.

5. `unset`: This builtin should remove an environment variable from the shell's environment with a name specified by its argument.

6. `env`: This builtin should print all environment variables and their values to standard output.

7. `exit`: This builtin should exit the shell with an exit status specified by its optional argument (which defaults to 0 if not provided).

## How To Use

1. Clone this repo.
2. Run the `make` command.
3. Run the CMD
    ```
    $ ./minishell
    ```
ps : this project is only tested in MAC os, I don't know it's behavios in other os.

## Contributors
+ Samir Qatim    : [Sqatim](https://github.com/sqatim) 
+ Oussama Qatim : [Oqatim](https://github.com/oussamaqatim)