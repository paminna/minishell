#include "mini.h"

void	signal_ctrlc()
{
	write(1, "\n", 1);
	write(1, "Minishell>> ", 12);
}