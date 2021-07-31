#include "../mini.h"

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
	printf("old %s\n", getcwd(NULL, 1000));
	env_struct->new_dir = "..";
	env_struct->old_dir = getcwd(NULL, 1000);
	if (chdir(env_struct->new_dir) < 0)
		return(strerror(errno));
	printf("new %s\n", getcwd(NULL, 1000));
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