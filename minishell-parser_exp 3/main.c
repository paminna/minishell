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

void	parser_export2(char *massiv, t_env *env_struct, char **env)
{
	int i;
	int sm; // 1 если ошибка
	// t_list_env struct_export;
	printf("massiv %s\n", massiv);
//	if (massiv == NULL)
//		ft_start_exp(env, env_struct);
	env_struct->value = ft_strdup(massiv); // вся строка (str=3ptr)
	env_struct->key = parser_key_export(env_struct->value); //ключ (str)
	while(*massiv)
	{
		if(*massiv == '=')
			env_struct->str = parser_env_export(env_struct->value); //значение с равно (=ptr3)
		massiv++;
	}
	sm = 0;
	if (ft_isdigit(env_struct->key[i]) )// если ПЕРВЫЙ символ в ключе цифры или символ, кроме _ : ошибка
		sm = 1;
	i = -1;
	printf("%s\n", env_struct->key);
	while (env_struct->key[++i]) //если в ключе содержаться символы кроме букв, цифр и _ ошибка
	{
		if (ft_isdigit(env_struct->key[i]) || env_struct->key[i] == '_')
			sm = 1;
	}
	printf("hey");
	if(sm != 1)
	    ft_start_exp(env, env_struct);
	if (sm == 1) // в случае ошибки в ключе
	{
//		write(2, "Minishell>> ", 12);
		write(2,"export: ", 8);
		write(2,"\'", 1);
//		printf("hey\n");
		ft_putstr_fd(env_struct->value, 2); //TODO + очищение памяти
		free(env_struct->key);
		free(env_struct->value);
		write(2,"\'", 1);
		write(2,": not a valid identifier\n", 25);
//		free(env_struct->key);
//		free(env_struct->value);
//		return ;
	}
//	if (sm == 0)
//	{
//
//	}
}

void parser_export(char **massiv, t_env *env_struct, char **env)
{
	printf("%s\n",massiv[1]);
//	printf("hey\n");
	// if(massiv[1] != NULL)
    env_struct->key = NULL; // инициаилизатор
    if (massiv[1] == NULL)
        ft_start_exp(env, env_struct);
    else
        parser_export2(massiv[1], env_struct, env);
}

void my_exit(char **str)
{
	if (str[1] == NULL)
		exit (0);
}

void find_command(t_all *all, char **env)
{
	t_env env_struct;

	if (!ft_strncmp(all->result[0], "echo", 5))
		parser_echo(all->result);
	else if (!ft_strncmp(all->result[0], "export", 7))
		parser_export(all->result, &env_struct, env);
	else if (!ft_strncmp(all->result[0], "cd", 3))
		ft_cd(&env_struct);// если пусто тильда или записать new_dir
	else if (!ft_strncmp(all->result[0], "pwd", 4))
		ft_pwd();
	// else if (!ft_strncmp(all->result[0], "unset", 6))
	// 	parser_unset(all->result);
	else if (!ft_strncmp(all->result[0], "env", 4))
		ft_out_env(&env_struct);
	else if (!ft_strncmp(all->result[0], "exit", 5))
		my_exit(all->result);
	// else
	// 	write(2, "Minishell>> ", 12);

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
		if (*str != '\\')
			s[i++] = *str;
		else if (*(str + 1) == '\\')
			s[i++] = *str++;
		str++;
	}
	s[i] = '\0';
	return (s);
}

char	*before(char **str)
{
	int		count;
	char	*s;
	int		i;

	s = *str;
	count = 0;
	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\"' && s[i] != '\'' \
				&& s[i] != '$' && s[i] != '>' && s[i] != '<' && s[i] != '|')
	{
		count++;
		if (s[i] == '\\')
			i++;
		i++;
	}
	s = ft_new(*str, count);
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



// char *check_env(char **str)
// {

// }

char *parser_result(char **str)
{
	if(**str == '\"')
		return(check_double_quotes(str));
	else if(**str == '\'')
		return(check_single_quotes(str));
	// else if (**str == '$')
	// 	return(check_env(str));
	else
		return(before(str));
}




// void  redirect_output(t_list *output, t_all *all, int error)
// {
// 	char *str;
// 	int n_fd;
// 	t_red *red;
// 	int pid;
// 	int fd_for_input;
// 	int fd_for_output;
// 	char *n;

// 	pid = 0;
// 	if (error)
// 	{
// 		if (output)
// 		{
// 			str = output->content;
// 			n_fd = open(++str, O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
// 			if (n_fd < 0)
// 				exit(1);
// 			close(n_fd);
// 		}
// 		ft_putstr_fd(red->input, 2);
// 		write(1, ": No such file or directory\n", 28);
// 	}
// 	while (output && output->next)
// 	{
// 		str = output->content;
// 		n_fd = open(++str, O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
// 		if (n_fd < 0)
// 			exit(1);
// 		close(n_fd);
// 		output = output->next;
// 	}
// 	if (!error)
// 	{
// 		pid = fork();
// 		if (pid > 0)
// 			wait(NULL);
// 		else if (pid == 0)
// 		{
// 			all->pipe_f = 1;
// 			if (red->input)
// 			{
// 				fd_for_input = open(red->input, O_RDONLY);
// 				if(fd_for_input < 0)
// 					exit(1);
// 				close(fd_for_input);
// 			}
// 			else if (output)
// 			{
// 				n = (char *)output->content;
// 				if (n[0] == '1')
// 				{
// 					fd_for_output = open(++n, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 					if (fd_for_output < 0)
// 						exit(1);
// 				}
// 				else if (n[0] == '2')
// 				{
// 					fd_for_output = open(++n, O_RDWR | O_CREAT | O_TRUNC, 0666);
// 					if (fd_for_output < 0)
// 						exit(1);
// 				}
// 				dup2(fd_for_output, 1);
// 				close(fd_for_output);
// 			}
// 			find_command(all, env_struct, env);
// 		}
// 	}

// }

void	clear_list(t_cnt *cnt)
{
	ft_cntlear(&cnt->list, free);
	cnt->count = 0;
}
// void	parser_redirect(char **str, t_all *all, t_cnt	*words)
// {
// 	t_red red;
// 	char *s;

// 	ft_bzero(&red, sizeof(red));
// 	s = *str;
// 	while(*s!= '\0')
// 	{
// 		if (*s == '>' && *(s + 1) != '>')
// 			s = output_red(s, &red);
// 		else if (*s == '>' && *(s + 1) == '>')
// 			s = output_red1(s, &red);
// 		else if (*s == '<')
// 			s = input_red(s, all, &red);
// 		else if (*s == ' ')
// 			s = space_red(s, words);
// 		 s++;
// 	}
// 	allocate_mem(all, words);
// 	redirect_output(red.output, all, red.err);
// 	if (*s == '|')
// 		s++;
// 	s = skip_space(s);
// 	clear_list(words);
// }
void 		list_count(t_cnt *words, void *s)
{
	ft_lstadd_back(&words->list, ft_lstnew(s));
	words->count++;
}

void allocate_mem(t_all *all, t_cnt *words)
{
	int j;
	t_list *tmp;

	tmp = words->list;
	all->result = malloc(sizeof(char *) * (words->count + 1));
	all->result[words->count] = NULL;
	j = 0;
	while (j < words->count)
	{
		all->result[j++] = tmp->content;
		tmp = tmp->next;
	}
}
void	ft_cntlear(t_list **lst, void (*del_f)(void *))
{
	t_list	*temp_lst;
	t_list	*to_del_node;

	if ((!lst && !(*lst) && !del_f) || !lst || !(*lst) || !del_f)
		return ;
	temp_lst = *lst;
	while (temp_lst)
	{
		if (temp_lst->content)
			del_f(temp_lst->content);
		to_del_node = temp_lst;
		temp_lst = temp_lst->next;
		free(to_del_node);
	}
	*lst = NULL;
}

void	clear_lst(t_cnt *cnt)
{
	ft_cntlear(&cnt->list, free);
	cnt->count = 0;
}
void process(t_all *all, t_cnt *words, t_cnt *pipes, char **str, char **env)
{
	if (words->count != 0)
	{
		allocate_mem(all, words);
		list_count(pipes, all->result);
		if(pipes->count == 1)
		// if (ft_strlen(all->result[0]) > 0)
			find_command(all, env);
	}
	clear_lst(words);
	clear_lst(pipes);
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

t_all *parser(char *str, t_all *all, char **env)
{
	t_cnt	words;
	t_cnt	pipes;
	int		count;
	int		j;
	//int		len;
	char	*s;

	count = 0;
	ft_bzero(&words, sizeof(t_cnt));
	ft_bzero(&pipes, sizeof(t_cnt));
	while (*str != '\0')
	{
		str = skip_space(str);
		check_sim(str);
		// if (*str == '<' || *str == '>')
		// 	parser_redirect(&str, all, &words);
		s = parser_result(&str);
		list_count(&words, s);
		str = skip_space(str);
		if (*str == '|')
		{
			if (words.count > 0)
			{
				allocate_mem(all, &words);
				if (all->result)
					list_count(&pipes, all->result);
//				else
//					error
				clear_list_w(&words);
				str++;
			}
		}
	}
	process(all, &words, &pipes, &str, env);
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

//static void ft_init(t_parser *par)
//{
//	par->history = ft_calloc(500, sizeof(char*));
//	if(!par->history)
//		error("Allocated error", 11);
//	par->str = ft_calloc(2, sizeof(char*));
//	if(!par->str)
//		error("Allocated error", 11);
//	par->buf = NULL;
//}


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

// void	init_env(t_all *all, char **env)
// {
// 	int i;
// 	int n;
// 	t_env1 *get_env;

// 	i = 0;
// 	get_env = (t_env1 *) ft_calloc(1, sizeof(t_env1));
// 	while (env[i] != NULL)
// 	{
// 		n = 0;
// 		n = ft_len(&env[i], 0);
// 		get_env->key = ft_substr(env[i], 0, n);
// 		if (env[i][n] == '=')
// 		{
// 			n++;
// 			get_env->val = ft_substr(env[i], n, ft_strlen(&env[i][n]));
// 		}
// 		else
// 			get_env->val = NULL;
// 		create_new_env(&all->env, get_val_ket(get_env->key, get_env->val));
// 		i++;
// 	}
// }

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


// void	get_env(char **env, t_all *all)
// {
// 	int		count;
// 	int		len;
// 	char	*key;
// 	char	*val;

// 	count = 0;
// 	while (env[count] != NULL)
// 	{
// 		len = 0;
// 		while (env[count][len] != '=' && env[count][len] != '\0')
// 			len++;
// 		key = ft_substr(env[count], 0, len);
// 		if (env[count][len] == '=')
// 		{
// 			len++;
// 			val = ft_substr(env[count], len, ft_strlen(&env[count][len]));
// 		}
// 		else
// 			val = NULL;
// 		add_element(&all->env, new_element(key, val));
// 		count++;
// 	}
// }

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

void	get_env(char **env, t_all *all)
{
	int		count;
	int		len;
	char	*key;
	char	*val;

	count = 0;
	while (env[count] != NULL)
	{
		len = 0;
		while (env[count][len] != '=' && env[count][len] != '\0')
			len++;
		key = ft_substr(env[count], 0, len);
		if (env[count][len] == '=')
		{
			len++;
			val = ft_substr(env[count], len, ft_strlen(&env[count][len]));
		}
		else
			val = NULL;
		add_element(&all->env, new_element(key, val));
		count++;
	}
}

//static void	init_history(t_history *history)
//{
//	history->index = history->last;
//	if (history->last > 0)
//		return ;
//	history->last = 0;
//	history->arr = (char **)malloc(sizeof(char *) * 2);
//	history->arr[history->last] = (char *) ft_calloc(1, sizeof(char));
//	history->arr[history->last + 1] = NULL;
//}

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
	t_parser pars;
	t_env env_struct;
	static t_history	history;

	env_struct.key = "name";
	env_struct.value = "=";

	all = (t_all *) ft_calloc(1, sizeof(t_all));
	get_env(env, all);
	ft_init_flags(&env_struct);
	ft_copy_env(env, &env_struct);
	if (ac > 1 && av[1] != NULL)
		ft_putstr_fd("Invalid arguments\n", 1);
	while (1)
	{
		 str = readline ("Minishell>> ");
		 if (str == NULL)
		 {
		 	write(1, "exit\n", 5);
		 	write(fd, "exit\n", 5);
		 	free(str);
		 	free(all);
		 	return (0);
		 }
		 if (str && *str)
		 {
		 	 write(fd, str, ft_strlen(str));
		 	 write(fd, "\n", 1);
		 	 //add_history(str);
		 	 parser(str, all, env);
		 	//free(str);
		 }
	}
	// close(fd);
	return 0;
}