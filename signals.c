#include "mini.h"

static int	g_signal;

void	signal_for_new_line(int sig)
{
	write(1, "\n", 1);
	if (!(waitpid(0, &g_signal, WNOHANG)))
		kill(1, SIGINT);
	else
	{
		write(1, "Minishell>> ", 19);
		g_signal = 1;
	}
	(void)sig;
}

void	signal_exit_from_cat(int sig)
{
	(void)sig;
	if (!(waitpid(-1, &g_signal, WNOHANG)))
		write(1, "Quit: 3\n", 8);
	g_signal = 0;
}
