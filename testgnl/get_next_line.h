#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 3
#endif

char		*get_next_line(int fd);
ssize_t		ft_chrpos(char *s, char c);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *src);
char		*ft_strjoin(const char *s1, const char *s2);
//char		*ft_strchr(const char *s, int c);
char 		*clean_dangling(char *s1, char *s2, char *s3);
//char 		*fetch_line(char *stash, char *line);
char	*ft_substr(const char *s, unsigned int start, size_t len);
#endif