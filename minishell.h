#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>

typedef	struct s_all
{
	char	**result;
	int		flag;
	int		i;
	char	**env;
}				t_all;

typedef struct s_env
{
	char	**env;
	char	**exp;
}				t_env;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

#endif