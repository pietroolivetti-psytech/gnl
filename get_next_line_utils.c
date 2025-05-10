#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	s3 = malloc(sizeof(char) * len);
	if (!s3)
		return (NULL);
	while (i < len && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (i + j < len && s2[j])
	{
		s3[j + i] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}

char	*ft_strdup(const char *src)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!new)
		return (NULL);
	while (*src)
		new[i++] = *src++;
	new[i] = '\0';
	return (new);
}

ssize_t		ft_chrpos(char *s, char c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_str;
	char	*s2;

	if (s == NULL)
		return (NULL);
	i = 0;
	len_str = ft_strlen(s);
	if (start >= len_str)
		return (ft_strdup(""));
	if ((len_str - start) < len)
		len = len_str - start;
	s2 = malloc(len + 1 * sizeof(char));
	if (!s2)
		return (NULL);
	while (i < len)
	{
		if (!s[start])
			return (s2);
		s2[i++] = s[start++];
	}
	s2[i] =  '\0';
	return (s2);
}