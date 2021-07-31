#include "mini.h"

void	ft_errors(char *str)
{
	int i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}


//void	ft_out_env(char *str, t_env *env_struct)
//{
//	int i;
//	int j;
//
//	i = 0;
//	j = 0;
//	while (i < env_struct->count_lines)
//	{
//		while (env_struct->env[i][j])
//		{
//			write(1, &env_struct->env[i][j], 1);
//			j++;
//		}
//		write(1, "\n", 1);
//		j = 0;
//		i++;
//	}
//}

void	ft_copy_env(char **env, t_env *env_struct)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	env_struct->count_lines = i;
	i = 0;
	env_struct->env = (char**)malloc(sizeof(char*) * (env_struct->count_lines + 1));
	if (!env_struct->env)
		ft_errors("malloc error");
	while (i < env_struct->count_lines)
	{
		env_struct->env[i] = ft_strdup(env[i]);
		i++;
	}
}

void	ft_init_flags(t_env *env_struct)
{
	env_struct->flags.empty_val = 0;
	env_struct->flags.new_key = 0;
	env_struct->flags.let_unset = 0;
	env_struct->flags.redir_b = 0;
	env_struct->flags.redir2_b = 0;
	env_struct->flags.redir_m = 0;
	env_struct->flags.redir2_m = 0;
}
