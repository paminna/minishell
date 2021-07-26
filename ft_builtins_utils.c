#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (s1 && s2 && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

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

void	ft_sort_exp(t_env *env_struct)
{
	int 	i;
	int 	j;
	char	*swap;

	i = 0;
	j = 0;
	while (i < env_struct->count_lines)
	{
		while (j < env_struct->count_lines - i - 1)
		{
			if (ft_strcmp(env_struct->exp[j], env_struct->exp[j + 1]) > 0)
			{
				swap = env_struct->exp[j];
				env_struct->exp[j] = env_struct->exp[j + 1];
				env_struct->exp[j + 1] = swap;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_check_all_keys(t_env *env_struct)
{
	int i;
	int j;
	// int len_key;

	i = 0;
	// while (ft_strcmp(env_struct->env[i], "TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n003vdrm00yvf5/T/") > 0)
	// 	i++;
	while (i != env_struct->count_lines - 1)
	{
		j = 0;
		while (env_struct->env[i][j] != '=' && env_struct->env[i][j] != '\0')
			j++;
		if (env_struct->env[i][j] == '=')
		{
			if (ft_strncmp(&env_struct->env[i][j], env_struct->key, ft_strlen(env_struct->key)))
				env_struct->flags.new_key = 1;
		}
		i++;
	}
}


// void	ft_check_key_val(t_env *env_struct)
// {
// 	if (!(ft_isalpha(env_struct->value[0]) || env_struct->value[0] == '_'))
// 		ft_errors("not a valid identifier");
// }

void	ft_check_exports(t_env *env_struct, char **env)
{
	int i;

	i = 0;
	// ft_check_key_val(env_struct);
	env_struct->flags.new_key = 0;

	// если добавляем ключ, нужно перемоллочить память на одну строку больше, поэтому очищаем старые маллоки
	if (env_struct->key)
	{
		free(env_struct->env); 
		free(env_struct->exp);
		env_struct->count_lines++;
	}
	env_struct->env = (char**)malloc(sizeof(char*) * (env_struct->count_lines + 1));
	env_struct->exp = (char**)malloc(sizeof(char*) * (env_struct->count_lines + 1));
	if (!env_struct->env)
		ft_errors("malloc error");
	while (i < env_struct->count_lines - 1)
	{
		env_struct->env[i] = ft_strdup(env[i]);
		env_struct->exp[i] = ft_strdup(env[i]);
		i++;
	}
	ft_check_all_keys(env_struct);
	env_struct->value = NULL; // вытащить в инициализатор
	if (env_struct->key && env_struct->flags.new_key && env_struct->value)
	{
		env_struct->exp[i] = ft_strjoin(env_struct->key, env_struct->value);
		env_struct->env[i] = ft_strjoin(env_struct->key, env_struct->value);
	}
	else if (env_struct->key && env_struct->flags.new_key)
	{
		env_struct->env[i] = ft_strdup(env_struct->key);
		env_struct->exp[i] = ft_strdup(env_struct->key);
	}
}

void	ft_copy_exp(char **env, t_env *env_struct)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	env_struct->count_lines = i;
	i = 0;
	printf("ft_copy_exp\n");
	ft_check_exports(env_struct, env);
	ft_sort_exp(env_struct);
	while (i < env_struct->count_lines)
	{
		env_struct->exp[i] = ft_strjoin("declare -x ", env_struct->exp[i]);
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


void	ft_out_exp(t_env *env_struct)
{
	int i;
	int j;
	char s;
	int len;

	i = 0;
	j = 0;
	s = 34;
	len = 0;
	while (i != env_struct->count_lines)
	{
		len = ft_strlen(env_struct->exp[i]);
		while (env_struct->exp[i][j] != '=' && env_struct->exp[i][j] != '\0')
		{
			write(1, &env_struct->exp[i][j], 1);
			j++;
		}
		if (env_struct->exp[i][j] == '=')
		{
			write(1, &env_struct->exp[i][j], 1);
			write(1, &s, 1);
			j++;
			while (j < len)
			{
				write(1, &env_struct->exp[i][j], 1);
				j++;
			}
			write(1, &s, 1);
		}
		write(1, "\n", 1);
		j = 0;
		i++;
	}
}

void	ft_check_unset_env(t_env *env_struct)
{
	int i;
	int	j;
	int k;

	j = 0;
	env_struct->len_key_unset= 0;
	i = 0;
	k = 0;
	while (env_struct->unset[i] != '\0')
	{
		if (env_struct->unset[i] == '=')
			ft_errors("not a valid identifier");
		i++;
		env_struct->len_key_unset++;
	}
	i = 0;
	while (env_struct->unset[k] != env_struct->env[i][j])  //идем по первым символам ключа ищем одинаковые
	{
		i++;
	}
	while (env_struct->env[i])
	{
		k = 0;
		j = 0;
		while (env_struct->unset[k] == env_struct->env[i][j])  //идем по символам ключей, проверяя их на равенство
		{
			k++;
			j++;
			if (k == env_struct->len_key_unset && env_struct->env[i][j] == '=') //дошли до конца ключа и смотрим что след. символ в матрице =
			{
				env_struct->flags.let_unset = 1;
				// env_struct->count_lines -= 1;
			}
		}
		i++;
	}
}

void	ft_check_name(char *str, char **rewrite_name)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str, "PWD", 3))
			rewrite_name = &str;
		else if (ft_strncmp(str, "OLD_PWD", 7))
			rewrite_name = &str;
		i++;
	}
}

// just for commit 
