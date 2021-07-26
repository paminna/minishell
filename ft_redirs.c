#include "minishell.h"

void	ft_redir_in(t_redirs *redir, t_all *all)
{
	int file;

	if (redir->redir2_in == 1)
	{
		file = open(redir->file, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (file < 0)
			ft_errors("error");
		dup2(file, all->fd_std_in);
		close(file);
	}
	else if (redir->redir_in == 1)
	{
		file = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (file < 0)
			ft_errors("error");
		dup2(file, all->fd_std_in);
		close(file);
	}
}

void	ft_redir_out(t_redirs *redir, t_all *all)
{
	int file;
	char *str;
	int i;

	redir = (t_redirs*)malloc(sizeof(t_redirs)); 
	// добавить в другое место, чтобы выделялась память под количество всех редиректов и под каждый отдельно
	str = (char*)malloc(1000);
	if (str == NULL)
		ft_errors("malloc");
	redir->redir2_out = 1;
	if (redir->redir2_out == 1)
	{
		printf("hey\n");
		while (1) //пока не сигналы
		{
			write(1, "<", 1);
			i = get_next_line(0, &str);
		}
	}
	else if (redir->redir_out == 1)
	{
		file = open(redir->file, O_RDONLY, 0666);
		if (file < 0)
			ft_errors("error");
			//
		dup2(file, all->fd_std_in);
		close(file);
	}
}

void	ft_redir(t_redirs *redir, t_all *all)
{
	// int 	file;
	// int		fd[2];

	if (redir->redir2_in || redir->redir_in)
		ft_redir_in(redir, all);
	else if (redir->redir2_out || redir->redir_out)
		ft_redir_out(redir, all);
	// добавить dup2(backup_in, file); но куда не понятно
	// добавить закрытие фдшников
}

void	ft_check_redirs(t_all *all)
{
	int i;

	i = 0;
	dup2(all->fd_std_in, 0); //инициализация
	dup2(all->fd_std_out, 1);
	while (i < all->num_of_redirs)
	{
		if (all->redirs[i].file != NULL)
			ft_redir(&all->redirs[i], all);
	}
	// all->backup_in = dup(0);
	// all->backup_out = dup(1);
}
