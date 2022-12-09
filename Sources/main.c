#include "../Headers/minishell.h"

void disableCtrlChars()
{
    struct termios term;
    int result;

    result = tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void initGlobalVariable()
{
    g_global.forkFlag = 0;
}

int main(int ac, char **av, char **envp)
{
    t_execution *execStruct;
    disableCtrlChars();
    initGlobalVariable();
    execStruct = executionInitialization(envp);
    minishellLoop(execStruct);
    return (0);
}