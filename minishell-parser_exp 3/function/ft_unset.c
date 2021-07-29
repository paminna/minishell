#include "../mini.h"

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