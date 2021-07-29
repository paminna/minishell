#include "mini.h"

void	signal_for_new_line()
{
	static int	g_signal;

	write(1, "\n", 1);
	if (!(waitpid(0, &g_signal, WNOHANG)))
		kill(1, SIGINT);
	else
	{
		write(1, "Minishell>> ", 12);
		g_signal = 1;
	}
	(void)g_signal;
}