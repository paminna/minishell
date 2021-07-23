#include "mini.h"
#include <curses.h>
#include <term.h>

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

void	parser_export2(char *massiv)
{
	int i;
	int sm; // 1 если ошибка
	t_list_env struct_export;

	struct_export.value = ft_strdup(massiv); // вся строка (str=3ptr)
	struct_export.key = parser_key_export(struct_export.value); //ключ (str)
	while(*massiv)
	{
		if(*massiv == '=')
			struct_export.str = parser_env_export(struct_export.value); //значение с равно (=ptr3)
		massiv++;
	}
	i = 0;
	sm = 0;
	if (ft_isdigit(struct_export.key[i]) ||
		(!ft_isalpha(struct_export.key[i]) && struct_export.key[i] != '_')) // если ПЕРВЫЙ символ в ключе цифры или символ, кроме _ : ошибка
		sm = 1;
	i = -1;
	while (struct_export.key[++i]) //если в ключе содержаться символы кроме букв, цифр и _ ошибка
	{
		if (!ft_isdigit(struct_export.key[i]) && !ft_isalpha(struct_export.key[i]) && struct_export.key[i] != '_')
			sm = 1;
	}
	if (sm == 1) // в случае ошибки в ключе
	{
		write(2, "Minishell>> ", 12);
		write(2,"export: ", 8);
		write(2,"\'", 1);
		ft_putstr_fd(struct_export.value, 2); //TODO + очищение памяти
		write(2,"\'", 1);
		write(2,": not a valid identifier\n", 26);
		return ;
	}
//	if (sm == 0)
//	{
//
//	}
}

void parser_export(char **massiv)
{
	if(massiv[1] != NULL)
		parser_export2(massiv[1]);
}

void my_exit(char **str)
{
	if (str[1] == NULL)
		exit (0);
}

void find_command(t_all *all)
{
	if (!ft_strncmp(all->result[0], "echo", 5))
		parser_echo(all->result);
	else if (!ft_strncmp(all->result[0], "export", 7))
		parser_export(all->result);
//	else if (!ft_strncmp(all->result[0], "cd", 3))
//		parser_cd(all->result);
//	else if (!ft_strncmp(all->result[0], "pwd", 4))
//		parser_pwd(all->result);
//	else if (!ft_strncmp(all->result[0], "unset", 6))
//		parser_unset(all->result);
//	else if (!ft_strncmp(all->result[0], "env", 4))
//		parser_env(all->result);
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

void	check_sim(char *str)
{
	int i;

	i = 0;
	if ((*str == '|' || *str == '&' || *str == ')'
		 || *str == '<' || *str == '>') && str[++i] == '\0')
	{
		write(2, "Minishell>> ", 12);
		write(2,"syntax error near unexpected token ", 35);
		write(2,"\'", 1);
		ft_putstr_fd(str, 2); //TODO + очищение памяти
		write(2,"\'\n", 3);
		return ;
	}
	if (*str == '%')
	{
		write(2, "Minishell>> ", 12);
		ft_putstr_fd(str, 2);
		write(2,": no such job\n", 15);
		return ;
	}
	if (*str == '^')
	{
		if (str[i] == '^' && (ft_isdigit(str[++i]) || ft_isalpha(str[++i])))
		{
			write(2, "Minishell>> ", 12);
			write(2,":s", 2);
			ft_putstr_fd(str, 2);
			write(2,": substitution failed\n", 22);
			return ;
		}
		else
		{
			write(2, "Minishell>> ", 12);
			write(2,":s", 2);
			ft_putstr_fd(str, 2);
			write(2,": no previous substitution\n", 27);
			return ;
		}
	}
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

//typedef struct s_pare
//{
//	char *str1;
//	char *str2;
//}t_pare;

//t_pare pare2()
//{
//	return((t_pare){.str1 = "abc", .str2 = "dce"});
//};

char *output_red(char *str, t_red *red)
{
	str = skip_space(str + 1);
	red->out_res = ft_strjoin(ft_itoa(1), parser_result(&str));
	while (*str != '\0' && *str != ' ' && *str != ' '
		   &&  *str != '|' &&  *str != '>' && *str != '<')
		red->out_res = ft_strjoin(red->out_res, parser_result(&str));
	ft_lstadd_back(&red->output, ft_lstnew((void *)red->out_res));
	return(str);
}

char *input_red(char *str, t_all *all,t_red *red)
{
	int fd;

	str = skip_space(++str);
	red->input = parser_result(&str);
	while (*str != '\0' && *str != ' ' && *str != ' '
		&&  *str != '|' &&  *str != '>' && *str != '<')
	{
		red->input = ft_strjoin(red->input, parser_result(&str));
		fd = open(red->input, O_RDONLY);
		if (fd < 0)
		{
			red->err = 1;
			while(*str != '\0' && *str != '|')
				str++;
		}
		else
			close(fd);
	}
	return(str);
}

char *output_red1(char *str, t_red *red)
{
	str = skip_space(str + 2);
	red->out_res = ft_strjoin(ft_itoa(2), parser_result(&str));
	while (*str != '\0' && *str != ' ' && *str != ' '
		   &&  *str != '|' &&  *str != '>' && *str != '<')
		red->out_res = ft_strjoin(red->out_res, parser_result(&str));
	ft_lstadd_back(&red->output, ft_lstnew((void *)red->out_res));
	return(str);
}

char *space_red(char *str, t_cnt *words)
{
	char *p;
	int e;

	str = skip_space(str);
	while (*str != '\0'
		   &&  *str != '|' &&  *str != '>' && *str != '<')
	{
		p = parser_result(&str);
		while (*str != '\0' && *str != ' ' && *str != '|')
			p = ft_strjoin(p, parser_result(&str));
		list_count(words, p);
		str = skip_space(str);
	}
	return(str);
}
void  redirect_output(t_list *output, t_all *all, int error)
{
	char *str;
	int n_fd;
	t_red *red;
	int pid;
	int fd_for_input;
	int fd_for_output;
	char *n;

	pid = 0;
	if (error)
	{
		if (output)
		{
			str = output->content;
			n_fd = open(++str, O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
			if (n_fd < 0)
				exit(1);
			close(n_fd);
		}
		ft_putstr_fd(red->input, 2);
		write(1, ": No such file or directory\n", 28);
	}
	while (output && output->next)
	{
		str = output->content;
		n_fd = open(++str, O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
		if (n_fd < 0)
			exit(1);
		close(n_fd);
		output = output->next;
	}
	if (!error)
	{
		pid = fork();
		if (pid > 0)
			wait(NULL);
		else if (pid == 0)
		{
			all->pipe_f = 1;
			if (red->input)
			{
				fd_for_input = open(red->input, O_RDONLY);
				if(fd_for_input < 0)
					exit(1);
				close(fd_for_input);
			}
			else if (output)
			{
				n = (char *)output->content;
				if (n[0] == '1')
				{
					fd_for_output = open(++n, O_RDWR | O_CREAT | O_TRUNC, 0644);
					if (fd_for_output < 0)
						exit(1);
				}
				else if (n[0] == '2')
				{
					fd_for_output = open(++n, O_RDWR | O_CREAT | O_TRUNC, 0666);
					if (fd_for_output < 0)
						exit(1);
				}
				dup2(fd_for_output, 1);
				close(fd_for_output);
			}
			find_command(all);
		}
	}

}

// void	ft_cntlear(t_list **lst, void (*del_f)(void *))
// {
// 	t_list	*temp_lst;
// 	t_list	*to_del_node;

// 	if ((!lst && !(*lst) && !del_f) || !lst || !(*lst) || !del_f)
// 		return ;
// 	temp_lst = *lst;
// 	while (temp_lst)
// 	{
// 		if (temp_lst->content)
// 			del_f(temp_lst->content);
// 		to_del_node = temp_lst;
// 		temp_lst = temp_lst->next;
// 		free(to_del_node);
// 	}
// 	*lst = NULL;
// }

void	clear_list(t_cnt *cnt)
{
	ft_cntlear(&cnt->list, free);
	cnt->count = 0;
}
void	parser_redirect(char **str, t_all *all, t_cnt	*words)
{
	t_red red;
	char *s;

	ft_bzero(&red, sizeof(red));
	s = *str;
	while(*s!= '\0')
	{
		if (*s == '>' && *(s + 1) != '>')
			s = output_red(s, &red);
		else if (*s == '>' && *(s + 1) == '>')
			s = output_red1(s, &red);
		else if (*s == '<')
			s = input_red(s, all, &red);
		else if (*s == ' ')
			s = space_red(s, words);
		 s++;
	}
	allocate_mem(all, words);
	redirect_output(red.output, all, red.err);
	if (*s == '|')
		s++;
	s = skip_space(s);
	clear_list(words);
}
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
void process(t_all *all, t_cnt *words, t_cnt *pipes, char **str)
{
	if (words->count != 0)
	{
		allocate_mem(all, words);
		list_count(pipes, all->result);
		if(pipes->count == 1)
		// if (ft_strlen(all->result[0]) > 0)
			find_command(all);
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
t_all *parser(char *str, t_all *all)
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
		if (*str == '<' || *str == '>')
			parser_redirect(&str, all, &words);
		s = parser_result(&str);
		list_count(&words, s);
//		ft_lstadd_back(&words, ft_lstnew(s));
//		count++;
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
	process(all, &words, &pipes, &str);
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

struct termios	init(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	return (term);
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

static void ft_init(t_parser *par)
{
	par->history = ft_calloc(500, sizeof(char*));
	if(!par->history)
		error("Allocated error", 11);
	par->str = ft_calloc(2, sizeof(char*));
	if(!par->str)
		error("Allocated error", 11);
	par->buf = NULL;
}

//void	canonical_input_on_with_exit(struct termios *term, int error)
//{
//	ft_putendl_fd("exit", 1);
//	tcgetattr(0, term);
//	term->c_lflag |= (ECHO);
//	term->c_lflag |= (ICANON);
//	tcsetattr(0, TCSANOW, term);
//	exit(error);
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
	while (env[n] != '\0' && env[n] != '=')
			n++;
	return (n);
}

void	init_env(t_all *all, char **env)
{
	int i;
	int n;
	t_env *get_env;

	i = 0;
	get_env = (t_env *) ft_calloc(1, sizeof(t_env));
	while (env[i] != NULL)
	{
		n = 0;
		n = ft_len(&env[i], 0);
		get_env->key = ft_substr(env[i], 0, n);
		if (env[i][n] == '=')
		{
			n++;
			get_env->val = ft_substr(env[i], n, ft_strlen(&env[i][n]));
		}
		else
			get_env->val = NULL;
		create_new_env(&all->env, get_val_ket(get_env->key, get_env->val));
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	char	str[500];
	int		i;
	t_all	*all;
	// struct termios	term;
	// int				fd;
	t_parser pars;

//	dup2(STDOUT_FILENO, 3);
//	dup2(STDIN_FILENO, 4);
//	signal(SIGQUIT, ft_quit);
//	signal(SIGINT, ft_sigint); //ctrl c
//	term = init();
//	fd = make_fd();
	all = (t_all *) ft_calloc(1, sizeof(t_all));
	init_env(all, env);
	if (ac > 1 && av[1] != NULL)
		ft_putstr_fd("Invalid arguments\n", 1);
	signal(SIGINT, signal_for_new_line);
	signal(SIGQUIT, signal_exit_from_cat);
	ft_init(&pars);
	while (1)
	{
		write(1, "Minishell>> ", 12);
		//tputs(save_cursor, 1, my_putchar);
		i = read(0, str, 1000);
		str[i - 1] = '\0';
		parser(str, all);
	}
//	return 0;
}