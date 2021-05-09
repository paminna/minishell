#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

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
	char 	*key;
	char	*value;
	int		max_len;
	int		count_lines;
}				t_env;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

#endif