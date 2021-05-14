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

typedef struct		s_list_env
{
	char			key;
	//char			*value;
}					t_list_env;

typedef struct s_all
{
	char		**result;
	int			i;
	char		**env;
	char		str;
}	t_all;

//t_all					*g_all;

// int		main(int argc, char **argv, char **env);
//t_all	*parser(char *line, t_all *all);
//void	parser(char *str, t_all *all);
int		main(int argc, char **argv, char **envp);
char *ft_strn(char **str, int len);

#endif
