#include <unistd.h>
#include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*buffer;
	size_t	i;

	i = -1;
	buffer = (char*)malloc(ft_strlen(s1) + 1);
	if (buffer == 0)
		return (NULL);
	while (s1[++i])
		buffer[i] = s1[i];
	buffer[i] = '\0';
	return (buffer);
}
