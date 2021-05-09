#include "minishell.h"
#include <stdio.h>

void	ft_errors(char *str)
{
	int i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	ft_echo(char *str, int flag)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		write(1, &str[i++], 1);
	if (flag == 1)
		write(1, "\n", 1);
}

void	ft_pwd()
{
	char 	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 1000);
	if (pwd == NULL)
	{
		ft_errors("pwd error");
	}
	while (pwd[i])
		write(1, &pwd[i++], 1);
	write(1, "\n", 1);
	free(pwd);
}

// int		ft_count_lines(char **env, t_env *env_struct)
// {
// 	int i;

// 	i = 0;
// 	env_struct->max_len = -1;
// 	while(env[i])
// 	{
// 		if (ft_strlen(env[i]) > env_struct->max_len)
// 			env_struct->max_len = ft_strlen(env[i]);
// 		i++;
// 	}
// 	return (i);
// }

void	ft_copy_env(char **env, t_env *env_struct)
{
	// int	count_lines;
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

void	ft_sort_exp(char **env, t_env *env_struct)
{
	int 	i;
	int 	j;
	char	*swap;

	// swap = (char*)malloc(env_struct->max_len + 1);
	i = 0;
	j = 0;
	while (i < env_struct->count_lines)
	{
		while (j < env_struct->count_lines - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)				//env[i][j] > env[i + 1][j]
			{
				swap = env[j];
				env[j] = env[j + 1];
				env[j + 1] = swap;
			}
			j++;
		}
		j = 0;
		i++;
	}
	// free(swap);
}

void	ft_copy_exp(char **env, t_env *env_struct)
{
	// int	count_lines;
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	env_struct->count_lines = i;
	i = 0;
	env_struct->exp = (char**)malloc(sizeof(char*) * (env_struct->count_lines + 1));
	if (!env_struct->exp)
		ft_errors("malloc error");
	ft_sort_exp(env, env_struct);
	while (i < env_struct->count_lines)
	{
		env_struct->exp[i] = ft_strjoin("declare -x ", env[i]);
		i++;
	}
}

void	ft_out_env(t_env *env_struct)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < env_struct->count_lines)
	{
		while (env_struct->env[i][j])
		{
			write(1, &env_struct->env[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		j = 0;
		i++;
	}
}

void	ft_check_exports(t_env *env_struct)
{
	
}

void	ft_out_exp(t_env *env_struct)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ft_check_exports(env_struct);
	while (env_struct->exp[i])
	{
		while (env_struct->exp[i][j])
		{
			write(1, &env_struct->exp[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		j = 0;
		i++;
	}
}


int main(int argc, char **argv, char **env)
{
	t_all *all;
	t_env env_struct;
	// int i = 0;

	ft_copy_env(env, &env_struct);
	ft_copy_exp(env, &env_struct);
	(void)argc;
	(void)argv;
	all = (t_all*)ft_calloc(1, sizeof(t_all));
	all->result = (char**)malloc(sizeof(char**) * 100);
	// all->result[0] = "echo";
	// all->result[1] = (char*)malloc(4);
	// all->result[1] = "pwd";
	// all->result[2] = (char*)malloc(4);
	// all->result[2] = "env";
	// all->result[3] = (char*)malloc(4);
	all->result[3] = "exp";
	all->flag = 0;
	// if (ft_strncmp(all->result[0], "echo", 3) == 0)
	// 	ft_echo(all->result[0], all->flag);
	// if (ft_strncmp(all->result[1], "pwd", 3) == 0)
	// 	ft_pwd();
	// if (ft_strncmp(all->result[2], "env", 3) == 0)
	// 	ft_out_env(all->result[2], &env_struct);
	if (ft_strncmp(all->result[3], "exp", 3) == 0)
		ft_out_exp(&env_struct);
}