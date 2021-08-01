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

	i = 0;
    env_struct->env = (char**)malloc(sizeof(char*) * (env_struct->count_lines + 1));
    env_struct->exp = (char**)malloc(sizeof(char*) * (env_struct->count_lines + 1));
    env_struct->copy_env = (char**)malloc(sizeof(char*) * (env_struct->count_lines + 1));
	if (!env_struct->env || !env_struct->exp || !env_struct->copy_env)
		ft_errors("malloc error");
	while (i < env_struct->count_lines)
	{
        env_struct->env[i] = ft_strdup(env[i]);
        env_struct->exp[i] = ft_strdup(env[i]);
        env_struct->copy_env[i] = ft_strdup(env[i]);
        i++;
	}
	printf("in env %d\n", env_struct->count_lines);
}

void init_all()
{
	t_all *all;

	all->str = 0;
	all->env = NULL;
	all->error = 0;
	all->i = 0;
	all->pipe_f = 0;
	all->flag = 0;
	all->flag_red = 0;
	all->result = NULL;
}

void	ft_init_flags(t_env *env_struct, char **env)
{
	int i;

	i = 0;
	env_struct->flags.empty_val = 0;
	env_struct->flags.new_key = 0;
	env_struct->flags.let_unset = 0;
	env_struct->flags.redir_b = 0;
	env_struct->flags.redir2_b = 0;
	env_struct->flags.redir_m = 0;
	env_struct->flags.redir2_m = 0;
	env_struct->flags.quotes = 0;
	env_struct->count_lines = 0;
	env_struct->env = NULL;
	env_struct->exp = NULL;
	env_struct->key = NULL;
	env_struct->len_key_unset = 0;
	env_struct->max_len = 0;
	env_struct->new_dir = NULL;
	env_struct->old_dir = NULL;
	env_struct->str = NULL;
	env_struct->value = NULL;
	env_struct->code = 0;
	while (env[i])
    {
	    i++;
	    env_struct->count_lines = i;
    }
	printf("before %d\n", env_struct->count_lines);
    ft_copy_env(env, env_struct);
	void init_all();
}
