#include "mini.h"

void	check_sim(char *str)
{
	int i;

	i = 0;
	if ((*str == '|' || *str == '&' || *str == ')'
		 || *str == '<' || *str == '>') && str[++i] == '\0')
	{
		write(2, "Minishell>> ", 12);
		write(2,"syntax error near unexpected token ", 35);
		write(2,"\'", 1);
		ft_putstr_fd(str, 2); //TODO + очищение памяти
		write(2,"\'\n", 3);
		return ;
	}
	if (*str == '%')
	{
		write(2, "Minishell>> ", 12);
		ft_putstr_fd(str, 2);
		write(2,": no such job\n", 15);
		return ;
	}
	if (*str == '^')
	{
		if (str[i] == '^' && (ft_isdigit(str[++i]) || ft_isalpha(str[++i])))
		{
			write(2, "Minishell>> ", 12);
			write(2,":s", 2);
			ft_putstr_fd(str, 2);
			write(2,": substitution failed\n", 22);
			return ;
		}
		else
		{
			write(2, "Minishell>> ", 12);
			write(2,":s", 2);
			ft_putstr_fd(str, 2);
			write(2,": no previous substitution\n", 27);
			return ;
		}
	}
}