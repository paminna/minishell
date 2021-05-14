#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//typedef struct		s_list_env
//{
//	void			*key;
//	void			*value;
//	struct s_list	*next;
//	struct s_list	*previous;
//}					t_list_env;

typedef struct s_all
{
	char		**result;
	int			i;
	char		**env;

}	t_all;


int		main(int argc, char **argv, char **envp);
char *ft_strn(char **str, int len);

#endif
