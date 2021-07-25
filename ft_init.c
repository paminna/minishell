#include "minishell.h"

void	ft_init_flags(t_env *env_struct, t_all *all)
{
	int i;

	i = 0;
	env_struct->flags.empty_val = 0;
	env_struct->flags.new_key = 0;
	env_struct->flags.let_unset = 0;
	all->num_of_redirs = 0;
	all->fd_std_in = 0;
	all->fd_std_out = 1;
	while (i < all->num_of_redirs)
	{
		all->redirs[i].redir_in = 0;
		all->redirs[i].redir2_in = 0;
		all->redirs[i].redir_out = 0;
		all->redirs[i].redir2_out = 0;
		all->redirs[i].file = NULL;
		i++;
	}
}