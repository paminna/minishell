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

void	my_echo(char **massiv)
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

void	parser_export(char **massiv)
{
	int i;
	int j;
	int flag; //если есть равно 1
	t_list_env struct_export;

	j = 0;
	i = 1;
	flag = 0;

	if (ft_isdigit(massiv[i][j]))
	{
		write(1, "export: `5=': not a valid identifier", 37); // нужна отдельная функция для ошибки
		exit(-1);
	}
	while(massiv[i][j] != '\0')
	{
		if(massiv[i][j] == '=')
			flag = 1; // отметили что есть =
		j++;
	}
	if(flag == 1)
	{
		while(massiv[i][j] != '=')
		{
			struct_export.key = malloc(sizeof(char) * (ft_strlen(j) + 1));
			struct_export.key = massiv[i][j];
			j++;
		}
	}
	write(1, &struct_export.key, 1);
}

void builtin_function_or_no(t_all *all)
{
	if (!ft_strncmp(all->result[0], "echo", 5))
		my_echo(all->result);
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

t_all *parser(char *str, t_all *all)
{
	t_list	*words = NULL;
	int		count;
	int		j;
	//int		len;
	char	*s;

	count = 0;
	while (*str != '\0')
	{
//		len = 0;
		str = skip_space(str);
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
		builtin_function_or_no(all);
		ft_free_arr(all->result);
	}
	//
//	 j = 0;
//	 while (all->result[j])
//	 	printf("%s\n", all->result[j++]);
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
	// ft_builtin_or_no(av);
	return 0;
}
