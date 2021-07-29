#include "mini.h"

t_gnl	lists(void)
{
	t_gnl list;

	list.size = 1;
	list.error = 0;
	list.pointer = NULL;
	return (list);
}

int		null_gnl(char *str)
{
	while (*str)
	{
		*str = '\0';
		str++;
	}
	return (1);
}

int		func_strdupjoin(char **string, char *p, int f)
{
	char *tmp;

	if (f)
	{
		*p = '\0';
		tmp = *string;
		if (!(*string = ft_strdup1(++p)))
			return (1);
		free(tmp);
		return (0);
	}
	else
	{
		tmp = *string;
		if (!(*string = ft_strjoin1(*string, p)))
			return (-1);
		free(tmp);
		return (0);
	}
}

char	*func_gnl(char *str, char **line, t_gnl *list)
{
	if (str)
	{
		if ((list->pointer = ft_strchr1(str, '\n')))
		{
			*list->pointer = '\0';
			if (!(*line = ft_strdup1(str)))
				list->error = 1;
			ft_strcpy1(str, ++list->pointer);
		}
		else
		{
			if (!(*line = ft_strdup1(str)))
				list->error = 1;
			null_gnl(str);
		}
	}
	else
	{
		if (!(*line = malloc(sizeof(char) * 1)))
			list->error = 1;
		**line = '\0';
	}
	return (list->pointer);
}

int		get_next_line(int fd, char **line)
{
	static char	*str;
	char		buf[BUFFER_SIZE + 1];
	t_gnl		list;

	list = lists();
	if (fd < 0 || !line || (read(fd, NULL, 0) < 0) || BUFFER_SIZE < 1)
		return (-1);
	list.pointer = func_gnl(str, line, &list);
	if (list.error == 1)
		return (-1);
	while (!list.pointer && (list.size = read(fd, buf, BUFFER_SIZE)))
	{
		buf[list.size] = '\0';
		if ((list.pointer = ft_strchr1(buf, '\n')))
			if (func_strdupjoin(&str, list.pointer, 1))
				return (-1);
		if (func_strdupjoin(line, buf, 0))
			return (-1);
	}
	if ((list.size || ft_strlen1(str)) ? 1 : 0)
		return (1);
	if (str)
		free(str);
	str = 0;
	return (0);
}
