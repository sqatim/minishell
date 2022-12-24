#include "../Headers/minishell.h"

t_global g_global;

void disable_ctrl_chars()
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void init_global_variable()
{
    g_global.forkFlag = 0;
    g_global.exit = 0;
}

int main(int ac, char **av, char **envp)
{
    t_execution *exec_struct;

    (void) av;
    if (ac == 1)
    {
        disable_ctrl_chars();
        init_global_variable();
        exec_struct = execution_initialization(envp);
        minishell_loop(exec_struct);
    }
    return (0);
}