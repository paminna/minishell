#include "minishell.h"

int	n_in_rem(char *str_n, char **remainder, char **line)
{
	char *tmp;
	char *tmp_2;

	*str_n++ = '\0';
	tmp = *remainder;
	tmp_2 = *line;
	*line = ft_strdup(*remainder);
	if (*line == NULL)
		return (-1);
	*remainder = ft_strdup(str_n);
	if (*remainder == NULL)
		return (-1);
	free(tmp);
	return (1);
}

int	r_less_null(char **remainder)
{
	free(*remainder);
	return (-1);
}

int	r_null(char **line, char **remainder)
{
	*line = ft_strdup(*remainder);
	if (*line == NULL)
		return (-1);
	free(*remainder);
	*remainder = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char *remainder;
	int			r;
	char		*str_n;
	char		buf[32 + 1];
	char		*tmp;

	if (fd < 0 || !line || 32 <= 0)
		return (-1);
	if (remainder == NULL && !(remainder = ft_strdup("")))
		return (-1);
	if ((str_n = ft_strchr(remainder, '\n')))
		return (n_in_rem(str_n, &remainder, line));
	while ((r = read(fd, buf, 32)) > 0)
	{
		buf[r] = '\0';
		tmp = remainder;
		remainder = ft_strjoin(remainder, buf);
		if (remainder == NULL)
			return (-1);
		free(tmp);
		if ((str_n = ft_strchr(remainder, '\n')))
			return (n_in_rem(str_n, &remainder, line));
	}
	return ((r < 0) ? r_less_null(&remainder) : r_null(line, &remainder));
}
// just for commit 