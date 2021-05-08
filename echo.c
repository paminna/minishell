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
	// if (!(ft_strncmp(str, "pwd", 3)))
	// 	ft_errors("wrong name");
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

int		ft_count_lines(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	return (i);
}

void	ft_copy_envp(char **env, t_env *env_struct)
{
	int	count_lines;
	int i;
	int j;

	i = 0;
	j = 0;
	count_lines = ft_count_lines(env);
	env_struct->env = (char**)malloc(sizeof(char*) * (count_lines + 1));
	if (!env_struct->env)
		ft_errors("malloc error");
	while (i < count_lines)
	{
		env_struct->env[i] = ft_strdup(env[i]);
		i++;
	}
}

void	ft_copy_exp(char **env, t_env *env_struct)
{
	int	count_lines;
	int i;
	int j;

	i = 0;
	j = 0;
	count_lines = ft_count_lines(env);
	env_struct->exp = (char**)malloc(sizeof(char*) * (count_lines + 1));
	if (!env_struct->exp)
		ft_errors("malloc error");
	while (i < count_lines)
	{
		env_struct->exp[i] = 
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	t_all *all;
	t_env env_struct;

	ft_copy_envp(env, &env_struct);
	// ft_copy_exp(env, &env_struct);
	(void)argc;
	(void)argv;
	all = (t_all*) malloc(1000);
	// all->result[0] = (char*)malloc(5);
	// all->result[0] = "echo";
	// all->result[1] = (char*)malloc(4);
	// all->result[1] = "pwd";
	// all->result[2] = (char*)malloc(4);
	// all->result[2] = "env";
	// all->flag = 0;
	// if (ft_strncmp(all->result[0], "echo", 3) == 0)
	// 	ft_echo(all->result[0], all->flag);
	// else if (ft_strncmp(all->result[0], "pwd", 3) == 0)
	// 	ft_pwd();
// 	else if (ft_strncmp(all->result[0], "env", 3) == 0)
// 		ft_env(all->result[2]);
}