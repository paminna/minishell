#include "mini.h"

size_t	ft_strlen1(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup1(const char *s)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!(str = malloc(((ft_strlen1(s) + 1)) * sizeof(char))))
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

char	*ft_strcpy1(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin1(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc((ft_strlen1(s1) + ft_strlen1(s2) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[k])
		str[i++] = s2[k++];
	return (str);
}

char	*ft_strchr1(const char *string, int symbol)
{
	char *str;

	str = (char *)string;
	while (*str != symbol)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}
