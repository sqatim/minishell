#include "../Headers/minishell.h"

void disableValueEndOfFile()
{
    struct termios term;
    int result;

    result = tcgetattr(STDIN_FILENO, &term);
    term.c_cc[VEOF] = _POSIX_VDISABLE;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    // printf("%lu\n",term.c_cc[VEOF]);
    // printf("%d\n", term.c_cc[VEOF]);
}

int main(int ac, char **av, char **envp)
{
    t_execution *execStruct;
    disableValueEndOfFile();
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