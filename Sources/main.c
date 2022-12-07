#include "../Headers/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_execution *execStruct;
    execStruct = executionInitialization(envp);
    // startParse(execStruct->env);
    minishellLoop(execStruct);
    // while (1)
    // {

    //     parsedCmd = parseCommand(av);
    //     checkCommand(parsedCmd);
    // }
    return (0);
}