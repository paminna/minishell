void	ft_check_all_keys(t_env *env_struct)
{
	int i;
	int j;
	int len_key;

	i = 0;
	j = 0;
	while (ft_strcmp1(env_struct->env[i], "TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n003vdrm00yvf5/T/") > 0)
		i++;
	while (env_struct->env[i]) //  проверка на новый ключ
	{
		while (env_struct->env[i][j])
		{
			if (env_struct->env[i][j] != '=')
				j++;
			else if (env_struct->env[i][j] == '=')
			{
				len_key = 0;
				while (env_struct->env[i][len_key] == env_struct->key[len_key] && len_key < j) // проверка что такого ключа нет
					len_key++;
				if (len_key != j - 1)
					env_struct->flags.new_key = 1;
				j++;
			}
		}
		j = 0;
		i++;
	}
}