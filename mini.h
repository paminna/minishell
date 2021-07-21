#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <term.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>


// # define STDIN 0
// # define STDOUT 1
// # define STDERR 2

// char **g_env;

// typedef struct s_signal // для обработки сигналов флаги
// {
// 	int sint;
// 	int squit;
// } t_sign;


typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_cnt
{
	t_list	*list;
	int		count;
}				t_cnt;

typedef struct		s_list_env
{
	char			*key;
	char			*value;
	char			*str;
}					t_list_env;

typedef struct s_red
{
	char **s;
	char *input;
	char *out_res;
	t_list *output;
	int err;
}t_red;

typedef struct s_all
{
	char		**result; // запись команд[0]
	int			i;
	char		**env;
	char		str;
}	t_all;

typedef	struct	s_parser
{
	char		**history;
	char		**comand;
	char		*buf;
	char		*str;
	int			len_str;
}				t_parser;

//t_all					*g_all;

// int		main(int argc, char **argv, char **env);
//t_all	*parser(char *line, t_all *all);
//void	parser(char *str, t_all *all);
int		main(int argc, char **argv, char **envp);
char	*screening_str(char *str, int len);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *str, size_t n);
void	*ft_memset(void *memptr, int val, size_t len);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
char	*ft_strdup(const char *str);
int	ft_isalpha(int ch);
int	ft_isdigit(int ch);
int	ft_strncmp(const char *str1, const char *str2, size_t n);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
int	ft_strcmp(const char *str1, const char *str2);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_itoa(int nbr);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_lstclear(t_list **lst, void (*del_f)(void *));
void 		list_count(t_cnt *words, void *s);
char	check_spec_s(char c);
char *new_str_with_q(char **str, int cnt_quot);
char *new_str_with_s_q(char **str, int cnt_quot);
char *check_double_quotes(char **str);
char *check_single_quotes(char **str);
void allocate_mem(t_all *all, t_cnt *words);
int	my_putchar(int c);

void	signal_exit_from_cat(int sig);
void	signal_for_new_line(int sig);

#endif
