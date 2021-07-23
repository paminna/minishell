#include "minishell.h"
#include <stdio.h>
#include <fcntl.h>

void	ft_errors(char *str)
{
	int i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}


// void	ft_echo(char *str, int flag)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		write(1, &str[i++], 1);
// 	if (flag == 1)
// 		write(1, "\n", 1);
// }

// void	ft_pwd()
// {
// 	char 	*pwd;
// 	int		i;

// 	i = 0;
// 	pwd = getcwd(NULL, 1000);
// 	if (pwd == NULL)
// 	{
// 		ft_errors("pwd error");
// 	}
// 	while (pwd[i])
// 		write(1, &pwd[i++], 1);
// 	write(1, "\n", 1);
// 	free(pwd);
// }

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

// void	ft_sort_exp(t_env *env_struct)
// {
// 	int 	i;
// 	int 	j;
// 	char	*swap;

// 	i = 0;
// 	j = 0;
// 	while (i < env_struct->count_lines)
// 	{
// 		while (j < env_struct->count_lines - i - 1)
// 		{
// 			if (ft_strcmp(env_struct->exp[j], env_struct->exp[j + 1]) > 0)
// 			{
// 				swap = env_struct->exp[j];
// 				env_struct->exp[j] = env_struct->exp[j + 1];
// 				env_struct->exp[j + 1] = swap;
// 			}
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// }

// void	ft_check_all_keys(t_env *env_struct)
// {
// 	int i;
// 	int j;
// 	int len_key;

// 	i = 0;
// 	j = 0;
// 	while (ft_strcmp(env_struct->env[i], "TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n003vdrm00yvf5/T/") > 0)
// 		i++;
// 	while (env_struct->env[i])
// 	{
// 		while (env_struct->env[i][j])
// 		{
// 			if (env_struct->env[i][j] != '=')
// 				j++;
// 			else if (env_struct->env[i][j] == '=')
// 			{
// 				len_key = 0;
// 				while (env_struct->env[i][len_key] == env_struct->key[len_key] && len_key < j)
// 					len_key++;
// 				if (len_key != j - 1)
// 					env_struct->flags.new_key = 1;
// 				j++;
// 			}
// 		}
// 		j = 0;
// 		i++;
// 	}
// }

// void	ft_check_key_val(t_env *env_struct)
// {
// 	if (!(ft_isalpha(env_struct->value[0]) || env_struct->value[0] == '_'))
// 		ft_errors("not a valid identifier");
// }

// void	ft_check_exports(t_env *env_struct, char **env)
// {
// 	int i;

// 	i = 0;
// 	ft_check_all_keys(env_struct);
// 	ft_check_key_val(env_struct);
// 	if (env_struct->key)
// 	{
// 		free(env_struct->env);
// 		env_struct->count_lines++;
// 	}
// 	env_struct->env = (char**)malloc(sizeof(char*) * (env_struct->count_lines + 1));
// 	env_struct->exp = (char**)malloc(sizeof(char*) * (env_struct->count_lines + 1));
// 	if (!env_struct->env)
// 		ft_errors("malloc error");
// 	while (i < env_struct->count_lines - 1)
// 	{
// 		env_struct->env[i] = ft_strdup(env[i]);
// 		env_struct->exp[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	if (env_struct->key && env_struct->flags.new_key && env_struct->value)
// 	{
// 		env_struct->exp[i] = ft_strjoin(env_struct->key, env_struct->value);
// 		env_struct->env[i] = ft_strjoin(env_struct->key, env_struct->value);
// 	}
// 	else if (env_struct->key && env_struct->flags.new_key)
// 	{
// 		env_struct->env[i] = ft_strdup(env_struct->key);
// 		env_struct->exp[i] = ft_strdup(env_struct->key);
// 	}
// }

// void	ft_copy_exp(char **env, t_env *env_struct)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (env[i])
// 		i++;
// 	env_struct->count_lines = i;
// 	i = 0;
// 	ft_check_exports(env_struct, env);
// 	ft_sort_exp(env_struct);
// 	while (i < env_struct->count_lines)
// 	{
// 		env_struct->exp[i] = ft_strjoin("declare -x ", env_struct->exp[i]);
// 		i++;
// 	}
// }

void	ft_out_env(char *str, t_env *env_struct)
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


// void	ft_out_exp(t_env *env_struct)
// {
// 	int i;
// 	int j;
// 	char s;

// 	i = 0;
// 	j = 0;
// 	s = 34;
// 	while (env_struct->exp[i])
// 	{
// 		while (env_struct->exp[i][j] != '=')
// 		{
// 			write(1, &env_struct->exp[i][j], 1);
// 			j++;
// 		}
// 		write(1, &env_struct->exp[i][j], 1);
// 		j++;
// 		write(1, &s, 1);
// 		while (env_struct->exp[i][j])
// 		{
// 			write(1, &env_struct->exp[i][j], 1);
// 			j++;
// 		}
// 		write(1, &s, 1);
// 		write(1, "\n", 1);
// 		j = 0;
// 		i++;
// 	}
// }

char	*ft_strdup(const char *s1)
{
	char	*buffer;
	size_t	i;

	i = -1;
	buffer = (char*)malloc(ft_strlen(s1) + 1);
	if (buffer == 0)
		return (NULL);
	while (s1[++i])
		buffer[i] = s1[i];
	buffer[i] = '\0';
	return (buffer);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

void	ft_unset(t_env *env_struct)
{
	int i;
	int j;
	int k;
	int c;

	c = 0;
	k = 0;
	i = 0;
	j = 0;
	ft_check_unset_env(env_struct);
	if (env_struct->flags.let_unset)
	{
		while (env_struct->unset[k] != env_struct->env[i][j])
		{
			while (env_struct->env[i][j])
			{
				write(1, &env_struct->env[i][j], 1);
				j++;
			}
			j = 0;
			write(1, "\n", 1);
			i++;
		}
		c = i;
		while (env_struct->env[c])
		{
			while (env_struct->unset[k] == env_struct->env[c][j])
			{	
				k++;
				j++;
			}
			if (!(env_struct->env[c][j] == '=' && k == env_struct->len_key_unset))
			{
				j = 0;
				while (env_struct->env[c][j])
					write(1, &env_struct->env[c][j++], 1);
				write(1, &"\n", 1);
			}
			k = 0;
			j = 0;
			c++;
		}
		// while (env_struct->unset[k] != env_struct->env[i][j])
		// {
		// 	printf("hey\n");
		// 	while (env_struct->env[i][j])
		// 	{
		// 		write(1, &env_struct->env[i][j], 1);
		// 		j++;
		// 	}
		// 	j = 0;
		// 	write(1, "\n", 1);
		// 	i++;
		// }
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new == NULL)
		return (NULL);
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	return (new);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = 0;
	if (src == NULL)
		return (0);
	if (dstsize > 0)
	{
		while (src[i] && (dstsize - i - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

void	ft_redir(char *str, t_env *env_struct)
{
	FILE 	*fp;
	char 	*cp;
	int		len;
	int 	file;
	int		fd[2];


	len = ft_strlen(str);
	cp = (char*)malloc(len + 4);
	cp = ft_strjoin(str,".txt");
	if (env_struct->flags.redir2_b == 1)
	{
		file = open(cp, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (file < 0)
			ft_errors("error");
		dup2(file, fd[1]);
		close(file);
	}
	else if (env_struct->flags.redir_b == 1)
	{
		file = open(cp, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (file < 0)
			ft_errors("error");
		dup2(file, fd[1]);
		close(file);
	}
}

int main(int argc, char **argv, char **env)
{
	t_all *all;
	t_env env_struct;

	env_struct.key = "name";
	env_struct.value = "=";
	// all->result[3] = (char*)malloc(5);
	// all->result[3] = "exp";
	ft_init_flags(&env_struct);
	ft_copy_env(env, &env_struct);
	// ft_copy_exp(env, &env_struct);
	(void)argc;
	(void)argv;
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
	// if (ft_strncmp(all->result[0], "echo", 3) == 0)
	// 	ft_echo(all->result[0], all->flag);
	// if (ft_strncmp(all->result[1], "pwd", 3) == 0)
	// 	ft_pwd();
	// if (ft_strncmp(all->result[2], "env", 3) == 0)
		// ft_out_env("env", &env_struct);
	// if (ft_strncmp(all->result[3], "exp", 3) == 0)
		// ft_out_exp(&env_struct);
	// if (ft_strncmp(all->result[4], "XPC_FLAGS", 3) == 0)
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
	env_struct.flags.redir_b = 1;
	ft_redir("hello", &env_struct);
}
