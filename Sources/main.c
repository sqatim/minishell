#include "../Headers/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_execution *execStruct;
    execStruct = executionInitialization(envp);
    minishellLoop(execStruct);
    // startParse(execStruct->env);
    // while (1)
    // {

    //     parsedCmd = parseCommand(av);
    //     checkCommand(parsedCmd);
    // }
    return (0);
}