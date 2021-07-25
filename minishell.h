#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
// #include "get_next_line.h"

typedef struct 	s_redirs
{
	int		redir_in;
	int		redir_out;
	int 	redir2_in;
	int		redir2_out;
	char	*file;
}				t_redirs;

typedef	struct	s_all
{
	char		**result;
	int			flag;
	int			i;
	char		**env;
	t_redirs	*redirs;
	int			num_of_redirs;
	int			fd_std_in;
	int			fd_std_out;
	int			count_args;
	char		*path;
}				t_all;

typedef	struct	s_flags
{
	int			new_key;
	int			empty_val;
	int			let_unset;
}				t_flags;

typedef struct	s_env
{
	char		**env;
	char		**exp;
	char 		*key;
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

//builtins
void	ft_echo(char *str, int flag);
void	ft_pwd();
void	ft_unset(t_env *env_struct);
char	*ft_cd(t_env *env_struct);
void	ft_exit(char *str, int code);
void	ft_copy_env(char **env, t_env *env_struct);
void	ft_copy_exp(char **env, t_env *env_struct);
void	ft_out_env(t_env *env_struct);
void	ft_out_exp(t_env *env_struct);
void	ft_check_name(char *str, char **rewrite_name);
void	ft_check_unset_env(t_env *env_struct);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_sort_exp(t_env *env_struct);
void	ft_check_all_keys(t_env *env_struct);
void	ft_check_key_val(t_env *env_struct);
void	ft_check_exports(t_env *env_struct, char **env);

//utils
void	ft_init_flags(t_env *env_struct, t_all *all);
void	ft_errors(char *str); //

// redirects
void	ft_redir_out(t_redirs *redir, t_all *all);
void	ft_check_redirs(t_all *all);
void	ft_redir(t_redirs *redir, t_all *all);
void	ft_redir_in(t_redirs *redir, t_all *all);

//get next line
int		get_next_line(int fd, char **line);
int		n_in_rem(char *str_n, char **remainder, char **line);
int		r_less_null(char **remainder);
int		r_null(char **line, char **remainder);



#endif