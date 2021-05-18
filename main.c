#include "mini.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	i = 0;
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
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

int	ft_isdigit(int ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return (1);
	return (0);
}

char	*ft_strdup(const char *str)
{
	char	*str1;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (str[len] != '\0')
		len++;
	str1 = (char*)malloc(sizeof(*str) * (len + 1));
	if (!str1)
		return (NULL);
	while (i < len)
	{
		str1[i] = str[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
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
		write(2,": not a valid identifier", 24);
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

void builtin_function_or_no(t_all *all)
{
	if (!ft_strncmp(all->result[0], "echo", 5))
		parser_echo(all->result);
		// else if (!ft_strncmp(all->str[0], "cd", 3))
		// 	my_cd(all);
		// else if (!ft_strncmp(all->str[0], "pwd", 4))
		// 	my_pwd(all);
	else if (!ft_strncmp(all->result[0], "export", 7))
		parser_export(all->result);
	// else if (!ft_strncmp(all->str[0], "unset", 6))
	// 	my_unset(all);
	// else if (!ft_strncmp(all->str[0], "env", 4))
	// 	my_env(all);
	// else if (!ft_strncmp(all->str[0], "exit", 5))
	// 	my_exit(all);
	// else if (!ft_strncmp(all->str[0], "kill", 5))
	// 	return ;
	// else
	// 	work_with_execve(all);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	if ((list = (t_list *)malloc(sizeof(t_list))))
	{
		list->content = content;
		list->next = NULL;
	}
	return (list);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *temp_lst;
	if (!new)
		return ;
	if (lst && *lst)
	{
		temp_lst = *lst;
		while (temp_lst->next)
			temp_lst = temp_lst->next;
		temp_lst->next = new;
	}
	else
		*lst = new;
}

void	*ft_memset(void *memptr, int val, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(memptr + i) = (unsigned char)val;
		i++;
	}
	return (memptr);
}

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void *pointer;

	pointer = (void *)malloc(count * size);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, count * size);
	return (pointer);
}


char *skip_space(char *str)
{
	while (*str != '\0' && *str == ' ')
		str++;
	return(str);
}

//char *single_quotes(*str)
//{
//	int		i;
//	int		len;
//	char	*argument;
//
//	//написать с изменением строки
//	i = 0;
//	len = 0;
//	while (str[i + len] != '\0' && str[i + len] != '\'')
//	{
//		len++;
//	}
//	argument = (char *)malloc(sizeof(char) * (len + 1));
//	while (i < len)
//	{
//		argument[i] = str[i];
//		i++;
//	}
//	return(argument);
//}

char *double_quotes(char **str)
{
	int i;
	char	*tmp;

	i = 0;
	(*str)++;
	tmp = *str;
	while(tmp[i] && tmp[i] != '\"')
		i++;
	tmp = ft_strn(str, i);
	(*str)++;
	return(tmp); ////peredelat'
}
//
//char *dollar(*str)
//{
//
//	return(str);
//}
//
//char *skip_spec(char *str)
//{
//	if (str == '\'')
//		single_quotes(str++);
//	else if (str == '"')
//		double_quotes(str++);
//	else if(str == '$')
//		dollar(str++);
//}
char *ft_list(char **str)
{
	int len;
	char *s;

	s = *str;
	len = 0;
	while (s[len] && s[len] != ' ' && s[len] != ';')
		len++;
	return (ft_strn(str, len));
}

char *ft_strn(char **str, int len)
{
	char	*s;
	int		i;
	char	*tmp;

	tmp = *str;
	i = 0;
	s = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		s[i] = tmp[i];
		i++;
	}
	//s[++i] = '\0';
	s[i] = '\0';
	*str += len;
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

//void	ft_quit(int sig)
//{
//	int		pid;
//	int		status;
//
//	(void)sig;
//	pid = waitpid(-1, &status, WNOHANG);
//	if (!pid)
//		write(1,"Quit: 3", 7);
//}
//
//void	ft_sigint(int sig)
//{
//	int		pid;
//	int		status;
//
//	pid = waitpid(-1, &status, WNOHANG);
//	if (sig == SIGINT)
//	{
//		write(1, "\n", 2);
//		if (pid)
//			write (1, "Minishell>> ", 12);
//	}
//}

void	check_sim(char *str)
{
	int i;

	i = 0;
	if ((*str == ';' || *str == '|' || *str == '&' || *str == ')'
		|| *str == '<' || *str == '>') && str[++i] == '\0')
	{
		write(2, "Minishell>> ", 12);
		write(2,"syntax error near unexpected token ", 35);
		write(2,"\'", 1);
		ft_putstr_fd(str, 2); //TODO + очищение памяти
		write(2,"\'", 1);
		return ;
	}
	if (*str == '%')
	{
		write(2, "Minishell>> ", 12);
		ft_putstr_fd(str, 2);
		write(2,": no such job", 35);
		return ;
	}
	if (*str == '^')
	{
		if (str[i] == '^' && (ft_isdigit(str[++i]) || ft_isalpha(str[++i])))
		{
			write(2, "Minishell>> ", 12);
			write(2,":s", 2);
			ft_putstr_fd(str, 2);
			write(2,": substitution failed", 22);
			return ;
		}
		else
		{
			write(2, "Minishell>> ", 12);
			write(2,":s", 2);
			ft_putstr_fd(str, 2);
			write(2,": no previous substitution", 26);
			return ;
		}
	}
}

char *parser_result(t_all *all, char *str)
{

	return(str);
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
t_all *parser(char *str, t_all *all)
{
	t_list	*words = NULL;
	int		count;
	int		j;
	//int		len;
	char	*s;

//	signal(SIGQUIT, ft_quit);
//	signal(SIGINT, ft_sigint);
	count = 0;
	while (*str != '\0')
	{
//		len = 0;
		str = skip_space(str);
		check_sim(str);
		//str = parser_result(all, str);
//		while (str[len] != '\0' && str[len] != ' ' && str[len] != ';')
//			len++;


//	if (*str == ';')
//		{
//			all->result = malloc(sizeof(char *) * (i + 1));
//			j = 0;
//			while (j < i)
//			{
//				all->result[j++] = words->content;
//				words = words->next;
//			}
//			builtin_function_or_no(all);
//			ft_free_arr(all->result);
//			//
//			//
//			i = 0;
//
//		}
		// if (*str == '\"')
		//	 s = double_quotes(&str);
		// else if (*str == '\'')
		//	 //ft_;
		//	 ;
		// else
		s = ft_list(&str);
		ft_lstadd_back(&words, ft_lstnew(s));
		count++;
		//str += len;
		str = skip_space(str);
		if (*str == ';')
		{
			if (count != 0)
			{
				all->result = malloc(sizeof(char *) * (count + 1));
				all->result[count] = NULL;
				j = 0;
				while (j < count)
				{
					all->result[j++] = words->content;
					words = words->next;
				}
				if (ft_strlen(all->result[0]) > 0)
					builtin_function_or_no(all);
				ft_free_arr(all->result);
				count = 0;
				str++;
			}
		}
	}
	if (count != 0)
	{
		all->result = malloc(sizeof(char *) * (count + 1));
		all->result[count] = NULL;
		j = 0;
		while (j < count) {
			all->result[j++] = words->content;
			words = words->next;
		}
		if (ft_strlen(all->result[0]) > 0)
			builtin_function_or_no(all);
		ft_free_arr(all->result);
	}
	//
//	 j = 0;
	//  while (all->result[j])
	//  	printf("%s\n", all->result[j++]);
	//

//// почистить листы (ft_lstlclear)
	return (all);
}

int main(int ac, char **av, char **env)
{
	char	str[500];
	int		i;
	t_list	*poka_tak;
	t_all	*all;

	write (1, "Minishell>> ", 12);
	all = (t_all *) ft_calloc(1, sizeof(t_all));
	i = read(0, str, 1000);
	str[i - 1] = '\0';
	// poka_tak = (t_list *)ft_calloc(1, sizeof(t_list));
	// get_env(env, poka_tak);
	parser(str, all);
	//write(1, "\n", 1);
	// ft_builtin_or_no(av);
	return 0;
}
