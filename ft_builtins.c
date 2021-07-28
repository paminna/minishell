#include "minishell.h"

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

void	ft_unset(t_env *env_struct)
{
	int i;
	t_env	env_copy;

	i = 0;
	if (!env_copy.env || !env_copy.exp)
		ft_errors("malloc");
	ft_check_unset_env(env_struct);
	if (env_struct->flags.let_unset)
	{
		while (env_struct->env[i])
		{
			if (!ft_strncmp(env_struct->env[i], env_struct->unset, env_struct->len_key_unset))
			{
				i++;
				env_copy.env[i] = ft_strdup(env_struct->env[i]);
				i++;
			}
			env_copy.env[i] = ft_strdup(env_struct->env[i]);
			i++;
		}
		i = 0;
		while (env_struct->exp[i])
		{
			if (!ft_strncmp(&(env_struct->exp[i][ft_strlen("declare -x ")]), env_struct->unset, env_struct->len_key_unset))
			{
				i++;
				env_copy.exp[i] = ft_strdup(env_struct->exp[i]);
				i++;
			}
			env_copy.exp[i] = ft_strdup(env_struct->exp[i]);
			i++;
		}
	}
	i = 0;
	while (env_struct->exp[i])
		free(env_struct->exp[i++]);
	i = 0;
	while (env_struct->env[i])
		free(env_struct->env[i++]);
	i = 0;
	while (env_copy.exp[i])
	{
		env_struct->exp[i] = ft_strdup(env_copy.exp[i]);
		i++;
	}
	i = 0;
	while (env_copy.env[i])
	{
		env_struct->env[i] = ft_strdup(env_copy.env[i]);
		i++;
	}
}

char	*ft_cd(t_env *env_struct)
{
	int i;
	int j;

	j = 0;
	i = 0;
	env_struct->old_dir = getcwd(NULL, 1000);
	if (chdir(env_struct->new_dir) < 0)
		return(strerror(errno));
	env_struct->new_dir = getcwd(NULL, 1000);
	while (i != env_struct->count_lines && env_struct->env[i][j])
	{
		if (env_struct->env[i][j] == 'O')
			ft_check_name(env_struct->env[i], &env_struct->old_dir);
		else if (env_struct->env[i][j] == 'P')
			ft_check_name(env_struct->env[i], &env_struct->new_dir);
		// else
			//создать переменную
		i++;
	}
	i = 0;
	while (i != env_struct->count_lines && env_struct->exp[i][j])
	{
		if (env_struct->exp[i][j] == 'O')
			ft_check_name(env_struct->exp[i], &env_struct->old_dir);
		else if (env_struct->exp[i][j] == 'P')
			ft_check_name(env_struct->exp[i], &env_struct->new_dir);
		// else
			// создать переменную
		i++;
	}
	// добавить возможность создания этих переменных если они были удалены
	return (NULL);
}

void	ft_exit(char *str, int code)
{
	if (!ft_strncmp(str, "exit", 4))
		exit(code);
}

// just for commit 
