#include "mini.h"

char	check_spec_s(char c)
{
	if (c == '\\' || c == '\"' || c == '\'')
		return (c);
	return (0);
}

char *new_str_with_q(char **str, int cnt_quot)
{
	char *save;
	char *s;
	int i;
	int n;

	save = *str;
	s = (char*)malloc(sizeof(char) * (cnt_quot + 1));
	i = 0;
	n = 0;
	while (i < cnt_quot)
	{
		if(save[n] == '\\' && check_spec_s(save[n + 1]))
			s[i++] = check_spec_s(save[++n]);
		if(save[n] != '\"')
			s[i++] = save[n];
		n++;
	}
	s[i] = '\0';
	*str = *str + cnt_quot;
	return(s);
}

char *new_str_with_s_q(char **str, int cnt_quot)
{
	char *save;
	char *s;
	int i;
	int n;

	save = *str;
	s = (char*)malloc(sizeof(char) * (cnt_quot + 1));
	i = 0;
	n = 0;
	while (i < cnt_quot)
	{
		if(save[n] != '\'')
			s[i++] = save[n];
		n++;
	}
	s[i] = '\0';
	*str = *str + cnt_quot;
	return(s);
}

char *check_double_quotes(char **str)
{
	int i;
	int cnt_quot;
	char *s;

	i = 0;
	cnt_quot = 0;
	s = ++(*str);
	while (s[i] != '\0' && s[i] != '\"')
	{
		if (s[i] != '\"')
			cnt_quot++;
		if (s[i] == '\\' && check_spec_s(s[i + 1]))
			i++;
		i++;
	}
	s = new_str_with_q(str, cnt_quot);
	*str += i - cnt_quot;
	*str += (**str != 0);
	return (s);
}

char *check_single_quotes(char **str)
{
	int i;
	int cnt_quot;
	char *s;

	i = 0;
	cnt_quot = 0;
	s = ++(*str);
	while (s[i] != '\0' && s[i] != '\'')
	{
		if (s[i] != '\'')
			cnt_quot++;
		i++;
	}
	s = new_str_with_s_q(str, cnt_quot);
	*str += i - cnt_quot + 1;
	return (s);
}