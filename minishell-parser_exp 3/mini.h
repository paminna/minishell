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
# include <errno.h>
# include <string.h>
# include <term.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# define BUFFER_SIZE 1

typedef	struct	s_gnl
{
	int			size;
	int			error;
	char		*pointer;
}				t_gnl;

int				get_next_line(int fd, char **line);
char			*ft_strchr1(const char *string, int symbol);
char			*ft_strjoin1(char const *s1, char const *s2);
char			*ft_strcpy1(char *dest, char *src);
char			*ft_strdup1(const char *s);
size_t			ft_strlen1(const char *str);

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
	struct s_list_env	*next;
	struct s_list_env	*previous;
	char *str;
}					t_list_env;

// typedef struct s_env1
// {
// 	char *key;
// 	char *val;
// }t_env1;

typedef	struct	s_flags
{
	int			new_key;
	int			empty_val;
	int			let_unset;
	int			redir_b;
	int			redir_m;
	int			redir2_m;
	int			redir2_b;
	int         quotes;
}				t_flags;

typedef struct	s_env
{
	char		**env;
	char		**exp;
	char 		*key;
	char		*str;
	char		*value;
	char		unset[12];
	char		*old_dir;
	char		*new_dir;
	int			max_len;
	int			count_lines;
	int			len_key_unset;
	int			code;
	// char		**env_copy;
	t_flags		flags;
}				t_env;

// typedef struct s_env
// {
// 	char *key;
// 	char *val;
// }t_env;

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
	t_list_env  *env;
	int			i;
	int error;
	char		str;
	struct termios	term;
	int			pipe_f;
	int flag;
	int flag_red;
	// t_env		*env_struct;
}	t_all;

// typedef struct s_history
// {
// 	struct termios	term;
// 	char			*term_name;
// 	int				was_read;
// 	char			buf[10];
// 	char			**arr;
// 	char			*del_tmp;
// 	int				index;
// 	int				last;
// }					t_history;

// typedef	struct	s_parser
// {
// 	char		**history;
// 	char		**comand;
// 	char		*buf;
// 	char		*str;
// 	int			len_str;
// }				t_parser;

// t_all	g_all;

void	signal_for_new_line();
/*Функции для работы с терминалом*/

// void rl_replace_line();
// void		canonical_input_off(t_history *tmp);
// void		canonical_input_on(t_history *tmp);
// void		my_backspace(t_history *history);
// void		write_new_symbol(t_history *history);
// void		arrow_to_up(t_history *history);
// void		arrow_to_down(t_history *history);
// void		canonical_input_on_with_exit(struct termios *term, int error);
// void		signal_exit_from_cat(int sig);
//t_all					*g_all;

// int		main(int argc, char **argv, char **env);
//t_all	*parser(char *line, t_all *all);
//void	parser(char *str, t_all *all);
int main(int ac, char **av, char **env);
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
char	*ft_substr(char const *str, unsigned int start, size_t len);
char	*ft_strchr(const char *str, int chr);

void	signal_exit_from_cat(int sig);
void	signal_for_new_line(int sig);
void	ft_cntlear(t_list **lst, void (*del_f)(void *));

t_all *parser(char *str, t_all *all, char **env);
void	check_sim(char *str);
char *skip_space(char *str);
char	*before(char **str);
void clear_list_w(t_cnt *words);
void find_command(t_all *all, char **env);
char *parser_result(char **str);

void	clear_lst(t_cnt *cnt);

void process(t_all *all, t_cnt *words, t_cnt *pipes, char **str, char **env);
void	parser_echo(char **massiv);
void parser_export(char **massiv, t_env *env_struct, char **env);
void my_exit(char **str);

char	*ft_cd(t_env *env_struct);
void	ft_pwd();
void	ft_out_env(t_env *env_struct);

void	ft_init_flags(t_env *env_struct, char **env);
void	ft_copy_env(char **env, t_env *env_struct);
void	ft_errors(char *str);
void	ft_unset(t_env *env_struct);
void	ft_start_exp(char **env, t_env *env_struct);
void	ft_check_exports(t_env *env_struct, char **env);
void	ft_sort_exp(t_env *env_struct);

//static void	init_history(t_history *history);
//void	get_history_from_file(void);
int	delete_element_from_list(t_list_env **list, char *key);
void	clear_list(t_cnt *cnt);
#endif
