#include "mini.h"

// void process(t_all *all, t_cnt *words, t_cnt *pipes, char **str)
// {
// 	if (words->count != 0)
// 	{
// 		allocate_mem(all, words);
//         if (ft_strlen(all->result[0]) > 0)
//         {
//             *(*str + 1) = 0;
//             clear_lst(words);
// 	        clear_lst(pipes);
//         }
// 		list_count(pipes, all->result);
// 		if(pipes->count == 1)
// 		// if (ft_strlen(all->result[0]) > 0)
// 			find_command(all);
// 	}
// 	clear_lst(words);
// 	clear_lst(pipes);
// }

// char *parser_result(char **str)
// {
// 	if(**str == '\"')
// 		return(check_double_quotes(str));
// 	else if(**str == '\'')
// 		return(check_single_quotes(str));
// 	// else if (**str == '$')
// 	// 	return(check_env(str));
// 	else
// 		return(before(str));
// }
// char	*strjoin_free(char *str1, char *str2)
// {
// 	char	*p;

// 	if (!str1)
// 		return (str2);
// 	if (!str2)
// 		return (str1);
// 	p = ft_strjoin(str1, str2);
// 	free(str1);
// 	free(str2);
// 	return (p);
// }

// void	my_puterror(char *command, char *argument, char *my_error)
// {
// 	ft_putstr_fd("ebash again: ", 2);
// 	if (command)
// 		ft_putstr_fd(command, 2);
// 	if (argument)
// 		ft_putstr_fd(argument, 2);
// 	if (my_error)
// 		ft_putendl_fd(my_error, 2);
// }

// t_all *parser(char *str, t_all *all)
// {
// 	t_cnt	words;
// 	t_cnt	pipes;
// 	char	*s;

// 	ft_bzero(&words, sizeof(t_cnt));
// 	ft_bzero(&pipes, sizeof(t_cnt));
// 	while (*str != '\0')
// 	{
// 		str = skip_space(str);
// 		check_sim(str);
// 		// if (*str == '<' || *str == '>')
// 		// 	parser_redirect(&str, all, &words);
// 		s = parser_result(&str);
//         while (*str != '\0' && *str != ' ' && *str != ';' && *str != '|')
// 			s = strjoin_free(s, parser_result(&str));
// 		list_count(&words, s);
// 		str = skip_space(str);
// 		if (*str == '|')
// 		{
// 			if (words.count > 0)
// 			{
// 				allocate_mem(all, &words);
// 				if (**all->result)
// 					list_count(&pipes, all->result);
// 				else
// 			    {
// 			    	my_puterror("syntax error ", NULL, "'|'");
// 			    	all->error = 258;
// 			    	*(str + 1) = 0;
// 			    }
// 				clear_list_w(&words);
// 				str++;
// 			}
// 		}
// 	}
// 	process(all, &words, &pipes, &str);
// 	return (all);
// }