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

// void	ft_delete_equality_and_out(t_env *env_struct)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (env_struct->env[i])
// 	{
// 		if (env_struct->env[i][j] == '=')
// 		{
// 			while (env_struct->env[i][j])
// 				j++;
// 		}
// 	}
// }


// ft_unset()
// {
// 	while (i != env_struct->count_lines)
// 		{
// 			while (env_struct->env[i][j])
// 			{
// 				c = j;
// 				if (env_struct->unset[k] == env_struct->env[i][c])	
// 					while (env_struct->unset[k] == env_struct->env[i][c])
// 					{
// 						k++;
// 						c++;
// 					}
// 				if (c == env_struct->len_key_unset - 1)
// 					j = c;
// 				// write(1, &env_struct->env[i][j], 1);
// 				j++;
// 			}
// 			// write(1, "\n", 1);
// 			j = 0;
// 			k = 0;
// 			i++;
// 		}
// }

void	ft_unset(t_env *env_struct)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ft_check_unset(env_struct);
	if (env_struct->flags.let_unset)
	{
		free(env_struct->env);
		free(env_struct->exp);
		env_struct->env = (char**)malloc(sizeof(char*) * (env_struct->count_lines));
		env_struct->exp = (char**)malloc(sizeof(char*) * (env_struct->count_lines));
	}
	// ft_delete_equality_and_out(env_struct);
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
		i++;
	}
	i = 0;
	while (i != env_struct->count_lines && env_struct->exp[i][j])
	{
		if (env_struct->exp[i][j] == 'O')
			ft_check_name(env_struct->exp[i], &env_struct->old_dir);
		else if (env_struct->exp[i][j] == 'P')
			ft_check_name(env_struct->exp[i], &env_struct->new_dir);
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
