#include "minishell.h"

void	ft_find_path(char *str, t_env *env_struct)
{
	int i;
	char *path;
	char **split;

	i = 0;
	while (env_struct->env[i])
	{
		if (!ft_strncmp("PATH=", env_struct->env[i], 5))
			path = ft_strdup(env_struct->env[i]);
		i++;
	}
	i = 0;
	split = ft_split(path, ':');
	free(path);
	while (split[i])
	{
		if (ft_strnstr(split[i], str, ft_strlen(str)) != NULL)
			env_struct->path = ft_strdup(split[i]);
		i++;
	}
	i = 0;
	while (split[i])
		free(split[i++]);
}

void	ft_find_binary(char *str, t_env *env_struct)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || str[i] == '/')
		
	}
}

void	ft_check_binary(t_all *all, t_env *env_struct)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < all->count_args)
	{
		if (all->result[i][j] != '/')
			ft_find_path(all->result[i], env_struct);
		else
			ft_find_binary(all->result[i], env_struct);
		i++;
	}
}