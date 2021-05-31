#include "mini.h"

static size_t		ft_len(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}


void	ft_lstclear(t_list **lst, void (*del_f)(void *))
{
	t_list	*temp_lst;
	t_list	*to_del_node;

	if ((!lst && !(*lst) && !del_f) || !lst || !(*lst) || !del_f)
		return ;
	temp_lst = *lst;
	while (temp_lst)
	{
		if (temp_lst->content)
			del_f(temp_lst->content);
		to_del_node = temp_lst;
		temp_lst = temp_lst->next;
		free(to_del_node);
	}
	*lst = NULL;
}


char				*ft_itoa(int n)
{
	size_t	len;
	size_t	sign;
	char	*dst;

	len = ft_len(n);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	if (n < 0)
	{
		dst[0] = '-';
		sign = 1;
	}
	else
		sign = 0;
	while (len-- > sign)
	{
		if (n < 0)
			dst[len] = '0' + n % 10 * (-1);
		if (n >= 0)
			dst[len] = '0' + n % 10;
		n /= 10;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*s3;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s3 = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[j++] = s1[i++];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		s3[j++] = s2[i++];
	}
	s3[j] = '\0';
	return (s3);
}

void	ft_putendl_fd(char *s, int fd)
{
	int		len;
	int		i;
	char	endl;

	if (fd < 0 || s == NULL)
		return ;
	i = 0;
	endl = '\n';
	len = ft_strlen(s);
	while (i < len)
		write(fd, &s[i++], 1);
	write(fd, &endl, 1);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}


void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (!str1)
		return (-1);
	if (!str2)
		return (1);
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

int	ft_isdigit(int ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return (1);
	return (0);
}

char	*ft_strdup(const char *str)
{
	char	*str1;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (str[len] != '\0')
		len++;
	str1 = (char*)malloc(sizeof(*str) * (len + 1));
	if (!str1)
		return (NULL);
	while (i < len)
	{
		str1[i] = str[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}


t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	if ((list = (t_list *)malloc(sizeof(t_list))))
	{
		list->content = content;
		list->next = NULL;
	}
	return (list);
}


void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp_lst;

	if (!new)
		return ;
	if (lst && *lst)
	{
		temp_lst = *lst;
		while (temp_lst->next)
			temp_lst = temp_lst->next;
		temp_lst->next = new;
	}
	else
		*lst = new;
}

void	*ft_memset(void *memptr, int val, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(memptr + i) = (unsigned char)val;
		i++;
	}
	return (memptr);
}

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void *pointer;

	pointer = (void *)malloc(count * size);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, count * size);
	return (pointer);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0'))
	{
		if ((unsigned char)str1[i] == (unsigned char)str2[i])
			++i;
		else
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
}

