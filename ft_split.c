#include "mini.h"

static int  word_counter(char const *s, char c)
{
  int words;
  int i;

  words = 0;
  i = 0;
  while (s[i] == c && s[i] != '\0')
    i++;
  if (s[i] == 0)
    return (0);
  if (c == '\0')
    return (1);
  while (s[i])
  {
    while (s[i] != c && s[i] != '\0')
      i++;
    words++;
    while (s[i] == c)
      i++;
  }
  return (words);
}

static int  count_len(char const *s, char c)
{
  int i;
  int len;

  len = 0;
  i = 0;
  while (s[i] == c)
    i++;
  while (s[i] != c && s[i] != '\0')
  {
    i++;
    len++;
  }
  return (len);
}

static char  ft_clear_split(char **word)
{
  int i;

  i = 0;
  while (word[i] != NULL)
  {
    free(word[i]);
    i++;
  }
  free(word);
  return (NULL);
}

char    **ft_split(char const *s, char c)
{
  char  **words;
  int    i;
  int    j;
  int    len;

  i = -1;
  if (s == NULL)
    return (NULL);
  len = word_counter(s, c);
  if ((words = (char)malloc((len + 1) * sizeof(char *))) == 0)
    return (NULL);
  while (++i != len)
  {
    j = 0;
    while (*s == c && *s != '\0')
      s++;
    if ((words[i] = (char*)malloc(count_len(s, c) + 1)) == NULL)
      return (ft_clear_split(words));
    while (*s != c && *s != '\0')
      words[i][j++] = *s++;
    words[i][j] = '\0';
  }
  words[len] = NULL;
  return (words);
}