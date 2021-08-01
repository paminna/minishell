#include "mini.h"

int	ft_putchar(int smb)
{
	int	res;

	res = write (1, &smb, 1);
	return (res);
}

void	parser_echo(char **massiv)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	j = 1;
	i = 0;
	while (!ft_strncmp(massiv[++i], "-n", 2))
	{
		while (massiv[i][j] == 'n')
			j++;
		if (massiv[i][j] == '\0')
			flag = 1;
		else
			break ;
	}
	while (massiv[i] != NULL)
	{
		write(1, massiv[i], ft_strlen(massiv[i]));
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
}

char	*parser_key_export(char *value)
{
	int len_key;
	char *save_v;
	char *key;
	int count;

	len_key = 0;
	save_v = value;
	count = -1;
	while(*value != '\0')
	{
		if(*value == '=')
			break;
		len_key++;
		value++;
	}
	value = save_v;
	key = (char*)malloc((sizeof(char) * len_key) + 1);
	if (key == NULL)
		exit(-1); //TODO придумать функцию по очистке и выводе ошибок
	//error("Malloc error", 13);
	while(++count < len_key)
	{
		if(*value == '=')
			break;
		key[count] = value[count];
	}
	return(key);
}

char *parser_env_export(char *value)
{
	int len_str;
	char *str;
	int count;
	int i;
	char *save_v;

	len_str = 0;
	count = 0;
	save_v = value;
	while (*value != '=')
	{
		value++;
		count++;
	}
	if (*value == '=')
	{
		while(*value != '\0')
		{
			len_str++;
			value++;
		}
	}
	str = (char*)malloc((sizeof(char) * len_str) + 1); // плюс 2 для /0 и для =
	if (str == NULL)
		exit(-1); //TODO придумать функцию по очистке и выводе ошибок
	//error("Malloc error", 13);
	i = 0;
	value=save_v;
	while (value[count] != '\0')
	{
		str[i] = value[count];
		count++;
		i++;
	}
	return (str);
}

int	ft_isalnum(int smbl)
{
	if (ft_isalpha(smbl) || ft_isdigit(smbl))
		return (1);
	else
		return (0);
}

char    *return_key(char *str)    //из экспорта
{
    int i;
    char *res;

    i = 0;
    while (str[i] != '=')
        i++;
    res = (char*)malloc(i + 1);
    i = 0;
    while (str[i] != '=')
    {
        res[i] = str[i];
        i++;
    }
    return (res);
}

void	parser_export2(char **massiv, t_env *env_struct, char **env)
{
//	int i;
//	int j;
//	int sm; // 1 если ошибка
//	char *r;
//
//	i = 1;

	//env_struct->exp_arg =
// 	env_struct->str = ft_strdup(massiv); // вся строка (str=3ptr)
// 	env_struct->key = parser_key_export(env_struct->str); //ключ (str)
// //	if (massiv))
// //		env_struct->value = NULL;
// 	while(*massiv)
// 	{
// 		if (*massiv == '=')
// 			env_struct->value = parser_env_export(env_struct->str); //значение с равно (=ptr3)
// 		// else
// 		// 	env_struct->value = NULL;
// 		massiv++;
// 	}
// 	sm = 0;
// 	i = 0;
// 	if (env_struct->key[i] == '_' || !(ft_isalpha(env_struct->key[i])))// если ПЕРВЫЙ символ в ключе цифры или символ, кроме _ : ошибка
// 		sm = 1;
// 	i = -1;
// 	while (env_struct->key[++i]) //если в ключе содержаться символы кроме букв, цифр и _ ошибка
// 	{
// 		if (!(ft_isalnum(env_struct->key[i])) && env_struct->key[i] != '_')
// 			sm = 1;
// 	}
// 	if (sm != 1)
// 		ft_start_exp(env, env_struct);
// 	if (sm == 1) // в случае ошибки в ключе
// 	{
// 		write(2,"export: ", 8);
// 		write(2,"\'", 1);
// 		ft_putstr_fd(env_struct->str, 2); //TODO + очищение памяти
// 		free(env_struct->key);
// 		free(env_struct->str);
// 		write(2,"\'", 1);
// 		write(2,": not a valid identifier\n", 25);
// 	}
    int i;
    int j;

    i = 0;
    while (massiv[i])
        i++;
    env_struct->env_arg = (char**)malloc((sizeof(char*) * i));
    i = 1;
    j = 0;
    while (massiv[i])
    {
        printf("massiv %s\n", massiv[i]);
        env_struct->env_arg[j] = ft_strdup(massiv[i]);
        printf("env    %s\n", env_struct->env_arg[i]);  //не записывает стрдап
        i++;
        j++;
    }
    i = 0;
    while (env_struct->env_arg[i])
    {
        env_struct->key = return_key(env_struct->env_arg[i]);
        env_struct->value = ft_strchr(env_struct->env_arg[i], '=');
        printf("key    %s\n", return_key(env_struct->env_arg[i]));
        printf("value  %s\n", env_struct->value);
        i++;
    }
    //проверка ключа и значения как раньше, в случае ошибки вывод ошибки
}

void parser_export(char **massiv, t_env *env_struct, char **env)
{
//    env_struct->key = NULL; // инициаилизатор
    if (massiv[1] == NULL)
        ft_out_exp(env_struct);
    else
    {
        parser_export2(massiv, env_struct, env);
        export(env_struct);
    }
}

void my_exit(char **str)
{
	if (str[1] == NULL)
		exit (0);
}

void work_with_execve(t_all *all, char *mass)
{
	char **new_str;

	// if (mass[0] == '.')
	// {

	// }
	if (!(find_element(&all->env, "PATH")))
	{
		write(1, "Minishell>> 2: command not found\n", 20);
		return ;
		// return(ft_putchar(2));
	}
	//new_str = ft_split(find_element(&all->env, "PATH"), ':');


}

void find_command(t_all *all, char **env)
{
	printf("%d\n", all->env_struct.count_lines);
	if (!ft_strncmp(all->result[0], "echo", 5))
		parser_echo(all->result);
	else if (!ft_strncmp(all->result[0], "export", 7))
		parser_export(all->result, &all->env_struct, env);
	else if (!ft_strncmp(all->result[0], "cd", 3))
		ft_cd(&all->env_struct);// если пусто тильда или записать new_dir
	else if (!ft_strncmp(all->result[0], "pwd", 4))
		ft_pwd();
	// else if (!ft_strncmp(all->result[0], "unset", 6))
	// 	parser_unset(all->result);
	else if (!ft_strncmp(all->result[0], "env", 4))
		ft_out_env(&all->env_struct);
	else if (!ft_strncmp(all->result[0], "exit", 5))
		my_exit(all->result);
	else
		work_with_execve(all, all->result[0]);
}

char *skip_space(char *str)
{
	while (*str != '\0' && *str == ' ')
		str++;
	return(str);
}

char	*ft_new(char *str, int len)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(sizeof(char) * (len + 1));
	while (str && i < len)
	{
			s[i++] = *str;
		str++;
	}
	s[i] = '\0';
	return (s);
}

char	*before(char **str)
{
	char	*s;
	int		i;

	s = *str;
	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\"' && s[i] != '\'' \
				&& s[i] != '$' && s[i] != '>' && s[i] != '<' && s[i] != '|')
	{
		i++;
	}
	s = ft_new(*str, i);
	*str += i;
	return (s);
}


static void	ft_free_arr(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

char	*find_element(t_list_env **list, char *key)
{
	t_list_env	*tmp;
	int			len;

	if (list == NULL || key == NULL)
		return (NULL);
	else
	{
		len = ft_strlen(key);
		tmp = *list;
		while (tmp != NULL)
		{
			if (!ft_strncmp(tmp->key, key, len + 1))
				return (tmp->value);
			tmp = tmp->next;
		}
		return (NULL);
	}
}

char *ft_new_m(char *str, int len)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(sizeof(char) * (len + 1));
	while (str && i < len)
	{
		s[i++] = *str;
		str++;
	}
	s[i] = '\0';
	return (s);
}

char *check_env(char **str, t_all *all)
{
	char	*s;
	char	*p;
	int		i;

	*str += 1;
	p = *str;
	if(!**str)
	{
		write(1, "Minishell>> $: No such file or directory\n", 42);
		return (ft_strdup("$"));
	}
	if (**str == ' ')
	{
		write(1, "Minishell>> $: command not found\n", 33);
		return (ft_strdup("$"));
	}
	else if (**str == '?')
	{
		p++;
		*str = p;
		write(1, "Minishell>> 258: command not found\n", 36);
		return (ft_strdup("258"));
	}
	i = 0;
	while (p[i] && p[i] != ' ' && p[i] != '\"' && p[i] != '\''
				&& p[i] != '$' && p[i] != '>' && p[i] != '<')
		i++;
	p = ft_new_m(*str, i);
	// printf("p: %s/n", p);
	*str += i;
	s = find_element(&all->env, p);
	free(p);
	if (s)
		return (ft_strdup(s));
	return (s);
}

char *parser_result(char **str, t_all *all)
{
	if(**str == '\"')
		return(check_double_quotes(str));
	else if(**str == '\'')
		return(check_single_quotes(str));
	else if (**str == '$')
		return(check_env(str, all));
	else
		return(before(str));
}


void 		list_count(t_cnt *words, void *s)
{
	ft_lstadd_back(&words->list, ft_lstnew(s));
	words->count++;
}

void mem_for_result(t_all *all, t_cnt *words, int count_w)
{
	int n;
	t_list *tmp;

	n = 0;
	all->result = (char *)malloc(sizeof(char *) * (count_w + 1));
	all->result[count_w] = NULL;
	tmp = words->list;
	while (n < count_w)
	{
		all->result[n++] = tmp->content;
		tmp = tmp->next;
	}
}

static void	pipe_function(t_all *matur, int **buf_fd, int max, int i)
{
	if (i == 0)
	{
		close(buf_fd[i][0]);
		dup2(buf_fd[i][1], 1);
	}
	else 
	{
		if (i < max)
		{
			close(buf_fd[i - 1][1]);
			dup2(buf_fd[i - 1][0], 0);
			close(buf_fd[i][0]);
			dup2(buf_fd[i][1], 1);
		}
		else
		{
			close(buf_fd[i - 1][1]);
			dup2(buf_fd[i - 1][0], 0);
		}
	}
	matur->pipe_f = 1;
}

// static int	**create_arr_fd_and_pid(int count_pipe, int **buf_pid)
// {
// 	int	**buf_fd;
// 	int	i;

// 	buf_fd = (int **)malloc(sizeof(int *) * count_pipe);
// 	if (!buf_fd)
// 		return (NULL);
// 	i = -1;
// 	while (++i < count_pipe)
// 	{
// 		buf_fd[i] = (int *)malloc(sizeof(int) * 2);
// 		pipe(buf_fd[i]);
// 	}
// 	*buf_pid = (int *)malloc(sizeof(int) * (count_pipe + 1));
// 	return (buf_fd);
// }

// void parser_pipes(int p, t_list **mass, t_all *all, char **env)
// {
// 	int		*buf_pid;
// 	int		**buf_fd;
// 	t_list	*tmp;
// 	int		i;

// 	p = p -  1;
// 	buf_fd = create_arr_fd_and_pid(p, &buf_pid);
// 	tmp = *mass;
// 	i = 0;
// 	while (tmp != NULL)
// 	{
// 		all->result = tmp->content;
// 		buf_pid[i] = fork();
// 		if (buf_pid[i] > 0 && i != p)
// 			close(buf_fd[i][1]);
// 		else if (buf_pid[i] == 0)
// 		{
// 			pipe_function(all, buf_fd, p, i);
// 			find_command(all, env);
// 			free(buf_fd);
// 			exit (0);
// 		}
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	while (--i >= 0)
// 		waitpid(buf_pid[i], NULL, 0);
// }

void process(t_all *all, t_cnt *words, t_cnt *pipes, char **str, char **env)
{
	if (words->count > 0)
	{
		mem_for_result(all, words, words->count);
		list_count(pipes, all->result);
		if(pipes->count == 1)
			find_command(all, env);
//		else
//			parser_pipes(pipes->count, &pipes->list, all, env);
	}
	clear_list(words);
	clear_list(pipes);
}

void clear_list_w(t_cnt *words)
{
	t_list	*tmp;

	tmp = words->list;
	while (tmp)
	{
		tmp = tmp->next;
		free(words->list);
		words->list = tmp;
	}
	words->list = NULL;
	words->count = 0;
}

char	*strjoin_free(char *str1, char *str2)
{
	char	*p;

	if (!str1)
		return (str2);
	if (!str2)
		return (str1);
	p = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (p);
}


t_all *parser(char *str, t_all *all, char **env)
{
	t_cnt	words;
	t_cnt	pipes;
	int		j;
	//int		len;
	char	*s;

	ft_bzero(&words, sizeof(t_cnt));
	ft_bzero(&pipes, sizeof(t_cnt));
	while (*str != '\0')
	{
		str = skip_space(str);
		check_sim(str);
		// if (*str == '<' || *str == '>')
		// 	parser_redirect(&str, all, &words);
		s = parser_result(&str, all);
		while (*str != '\0' && *str != ' ' && *str != '|')
			s = strjoin_free(s, parser_result(&str, all));
		list_count(&words, s);
		str = skip_space(str);
		if (*str == '|')
		{
			if (words.count > 0)
			{
				mem_for_result(all, &words, words.count);
				if (**all->result)
					list_count(&pipes, all->result);
				// else
				// {
				// 	write(1, "syntax error ", 14);
				// 	all->error = 258;
				// 	*(str + 1) = 0;
				// }
					clear_list_w(&words);
					str++;
			}
		}
	}
	process(all, &words, &pipes, &str, env);
	// clear_list(&words);
	// clear_list(&pipes);
	return (all);
}

void	ft_quit(int sig)
{
	int		pid;
	int		status;

	(void)sig;
	pid = waitpid(-1, &status, WNOHANG);
	if (!pid)
		ft_putendl_fd("Quit: 3", 1);
}

void	ft_sigint(int sig)
{
	int pid;
	int status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sig == SIGINT)
	{
		write(1,"\n", 2);
		if (pid)
			write (1, "Minishell>> ", 12);
	}
}

void	error(char *str, int error)
{
	char *id;
	char *res;

	ft_putendl_fd(str, 2);
	id = ft_itoa(error);
	res = ft_strjoin("error=", id);
//	export_var(res);
	free(id);
	free(res);
	exit(error);
}

int	make_fd(void)
{
	int fd;

	fd = open("minishell_history", O_CREAT, S_IWRITE | S_IREAD);
	if (!(fd))
		error("Error when creating a file history", 1);
	fd = open("minishell_history", O_RDWR | O_TRUNC);
	if (!fd)
		error("Error occurred while opening the history file", 1);
	return (fd);
}


t_list_env	*get_val_ket(char *key,char *val)
{
	t_list_env *list;

	list = (t_list_env *)malloc(sizeof(t_list_env));
	if(!list)
		return(NULL);
	list->key = key;
	list->value = val;
	list->next = NULL;
	list->previous = NULL;
	return (list);

}

int create_new_env(t_list_env **list, t_list_env *new)
{
	t_list_env *tmp;

	if (!list || !new)
		return (1);
	if (*list)
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->previous = tmp;
	}
	else
		*list = new;
	return (0);
}

int ft_len(char **env, int n)
{
	while (env[n] != '\0' && !ft_strchr(env[n], '='))
			n++;
	return (n);
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


t_list_env	*new_element(char *key, char *value)
{
	t_list_env	*lst;

	lst = (t_list_env *)malloc(sizeof(t_list_env));
	if (!lst)
		return (NULL);
	lst->key = key;
	lst->value = value;
	lst->next = NULL;
	lst->previous = NULL;
	return (lst);
}


int	add_element(t_list_env **list, t_list_env *new)
{
	t_list_env	*tmp;

	if (!list || !new)
		return (1);
	if (*list)
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->previous = tmp;
	}
	else
		*list = new;
	return (0);
}

void	get_env(t_all *all, char **env)
{
	char	*key;
	char	*value;
	int		count;
	int		len;
	int		len_env;

	count = 0;
	while (env[count] && env[count] != NULL)
	{
		len = 0;
		while (env[count][len] != '=' && env[count][len] != '\0')
			len++;
		key = ft_substr(env[count], 0, len);
		if (env[count][len] == '=')
		{
			len++;
			len_env = ft_strlen(&env[count][len]);
			value = ft_substr(env[count], len, len_env);
		}
		else
			value = NULL;
		add_element(&all->env, new_element(key, value));
		count++;
		printf("%s\n",key);
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

int main(int ac, char **av, char **env)
{
	char	*str;
	int		i;
	t_all	*all;
	int				fd;
	// t_env env_struct;

	// all->env_struct.key = "name";
	// env_struct.value = "=";

	all = (t_all *) ft_calloc(1, sizeof(t_all));
	get_env(all, env);
	ft_init_flags(&all->env_struct, env);
//	ft_copy_env(env, &all->env_struct);  //вынесла в инициализатор
	if (ac > 1 && av[1] != NULL)
		ft_putstr_fd("Invalid arguments\n", 1);
	signal(SIGINT, signal_ctrlc);
	while (1)
	{
		str = readline ("Minishell>> ");
		if (str == NULL)
		{
			write(1, " exit\n", 6);
			// write(fd, "exit\n", 5);
			free(str);
			free(all);
		 	return (0);
		}
		if (str && *str)
		{
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
			add_history(str);
			parser(str, all, env);
			free(str);
		}
	}
	// close(fd);
	return 0;
}