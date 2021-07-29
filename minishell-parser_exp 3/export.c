#include "mini.h"

void	ft_copy_exp(char **env, t_env *env_struct)
{
	int i;
	int j;

	i = 0;
	j = 0;
//	while (env[i])
//		i++;
//	env_struct->count_lines = i;
	i = 0;
	ft_check_exports(env_struct, env);
	ft_sort_exp(env_struct);
	while (i < env_struct->count_lines)
	{
		env_struct->exp[i] = ft_strjoin("declare -x ", env_struct->exp[i]);
		i++;
	}
}

void	ft_sort_exp(t_env *env_struct)
{
	int 	i;
	int 	j;
	char	*swap;

	i = 1;
	j = 0;
	while (i <= env_struct->count_lines - 1)
	{
		while (j <= env_struct->count_lines - i - 1)
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

void	ft_out_exp(t_env *env_struct)
{
	int i;
	int j;
	char s;

	i = 0;
	j = 0;
	s = 34;
	while (env_struct->exp[i])
	{
		while (env_struct->exp[i][j] != '=')
		{
			write(1, &env_struct->exp[i][j], 1);
			j++;
		}
		write(1, &env_struct->exp[i][j], 1);
		j++;
		write(1, &s, 1);
		while (env_struct->exp[i][j])
		{
			write(1, &env_struct->exp[i][j], 1);
			j++;
		}
		write(1, &s, 1);
		write(1, "\n", 1);
		j = 0;
		i++;
	}
}

int     ft_strcmp1(const char *s1, const char *s2)
{
	size_t          i;
	unsigned char   *str1;
	unsigned char   *str2;
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

void	ft_check_all_keys(t_env *env_struct)
{
    int i;
    int j;
    // int len_key;

    i = 0;
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
    while (i < env_struct->count_lines)
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

void	ft_start_exp(char **env, t_env *env_struct)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i])
//	    printf("%s\n", env[i++]);
	    ++i;
	env_struct->count_lines = i;
	ft_copy_exp(env, env_struct);
//	i = 0;
//	while (env_struct->exp[i])
//        printf("%s\n", env_struct->exp[i++]);
    ft_out_exp(env_struct);
}