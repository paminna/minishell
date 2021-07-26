#include "minishell.h"

void	ft_errors(char *str)
{
	int i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	ft_is_builtin(t_all *all, t_env *env_struct)
{
	int i;

	i = 0;
	while (i < all->count_args)
	{
		if (ft_strncmp(all->result[i], "echo", ft_strlen(all->result[i])) == 0)
			ft_echo(all->result[i], all->flag);
		else if (ft_strncmp(all->result[i], "pwd", ft_strlen(all->result[i])) == 0)
			ft_pwd();
		else if (ft_strncmp(all->result[i], "env", ft_strlen(all->result[i])) == 0)
			ft_out_env(env_struct);
		else if (ft_strncmp(all->result[i], "export", ft_strlen(all->result[i])) == 0)
			ft_out_exp(env_struct);
		else if (ft_strncmp(all->result[i], "unset", ft_strlen(all->result[i])) == 0)
			ft_unset(env_struct);
		else if (ft_strncmp(all->result[i], "exit", ft_strlen(all->result[i])) == 0)
			ft_exit(all->result[i], env_struct->code);
		else if (ft_strncmp(all->result[i], "cd", ft_strlen(all->result[i])) == 0)
		{
			if (ft_cd(env_struct))
				ft_errors(ft_cd(env_struct));
		}
		i++;
	}
}

void	ft_find_path(char *str, t_env *env_struct)
{
	
}

void	ft_check_binary(t_all *all, t_env *env_struct)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < all->count_args)
	{
		if (all->result[i][j] == '$' || all->result[i][j] != '/')
			ft_find_path(all->result[i], env_struct);
		// else
		// 	ft_find_binary();
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	t_all all;
	t_env env_struct;

	// env_struct.key = "name";
	// env_struct.value = "=";
	// all->result[3] = (char*)malloc(5);
	// all->result[3] = "exp";
	// ft_init_flags(&env_struct, &all);
	// ft_copy_env(env, &env_struct);
	// ft_copy_exp(env, &env_struct);
	(void)argc;
	(void)argv;
	// all.redirs->redir2_out = 1;
	// printf("hey\n");
	// ft_redir_out(all.redirs, &all);
	// all = (t_all*)ft_calloc(1, sizeof(t_all));
	// all->result = (char**)malloc(sizeof(char**) * 100);
	// all->result[0] = "echo";
	// all->result[1] = (char*)malloc(4);
	// all->result[1] = "pwd";
	// all->result[2] = (char*)malloc(4);
	// all->result[2] = "env";
	// all->result[3] = (char*)malloc(4);
	// all->result[4] = (char)malloc(4);
	// all->result[4] = "XPC_FLAGS";
	// all->flag = 0;
	// if (ft_strncmp(all->result[0], "echo", ft_stlren(all->result[0])) == 0)
	// 	ft_echo(all->result[0], all->flag);
	// if (ft_strncmp(all->result[1], "pwd", ft_stlren(all->result[1])) == 0)
	// 	ft_pwd();
	// if (ft_strncmp(all->result[2], "env", ft_stlren(all->result[2])) == 0)
		// ft_out_env(&env_struct);
	// if (ft_strncmp(all->result[3], "exp", ft_stlren(all->result[3])) == 0)
		// ft_out_exp(&env_struct);
	// if (ft_strncmp(all->result[4], "XPC_FLAGS", ft_stlren(all->result[4])) == 0)
	// env_struct.unset[0] = 'T';
	// env_struct.unset[1] = 'E';
	// env_struct.unset[2] = 'R';
	// env_struct.unset[3] = 'M';
	// env_struct.unset[4] = '_';
	// env_struct.unset[5] = 'P';
	// env_struct.unset[6] = 'R';
	// env_struct.unset[7] = 'O';
	// env_struct.unset[8] = 'G';
	// env_struct.unset[9] = 'R';
	// env_struct.unset[10] = 'A';
	// env_struct.unset[11] = 'M';
	// ft_unset(&env_struct);
	// env_struct.new_dir = "..";
	// if (ft_cd(&env_struct))
	// 	ft_errors(ft_cd(&env_struct));
	// else 
	// 	printf("succeed\n");
	// ft_exit(all->result[6], env_struct.code);
	// env_struct.flags.redir_b = 1;
	// ft_redir("hello", &env_struct);

	while (1)
	{
		//readline(line);
		//add_history(line);
		//parse
		ft_check_redirs(&all);
		ft_is_builtin(&all, &env_struct);
		ft_check_binary(&all, &env_struct);
	}
}