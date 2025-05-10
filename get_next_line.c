#include "get_next_line.h"

char *build_buffer(char *stash, char *buffer)
{
	char *temp;

	// Stash vazia
	if (!stash)
	{
		stash = ft_strdup(buffer);
		return (stash);
	}
	temp = stash;
	stash = ft_strjoin(stash, buffer);
	if (!stash)
		return (clean_dangling(temp, buffer, NULL));
	free(temp);
	return (stash);
}
char	*read_buff(int fd, char *stash)
{
	ssize_t bytes;
	char *buffer;

	bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (clean_dangling(stash, buffer, 0));
	while (bytes)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		// Erro a ler
		if (bytes < 0)
			return(clean_dangling(buffer, stash, 0));
		// Fim do ficheiro
		if (!bytes) // || bytes < BUFFER_SIZE)
			break ;
		buffer[bytes] = '\0';
		stash = build_buffer(stash, buffer);
		if (!stash)
			break ;
		if (ft_chrpos(stash, '\n') > -1)
			break ;
		// Confirmar se stash nao foi mal alocada
	}
	free(buffer);
	return (stash);
}

char *clean_dangling(char *s1, char *s2, char *s3)
{
	if(s1)
	{
		free(s1);
		s1 = NULL;
	}
	if(s2)
	{
		free(s2);
		s2 = NULL;
	}
	if(s3)
	{
		free(s3);
		s3 = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char *stash;
	char 		*remainder;
	char		*line;
	ssize_t		nl_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL); //(clean_dangling(stash, NULL, NULL));
	stash = read_buff(fd, stash);
	if (!stash || !stash[0])
		return(free(stash), stash = NULL, NULL);//(clean_dangling(stash, NULL, NULL));
	nl_pos = ft_chrpos(stash, '\n');
	if (nl_pos != -1 && (nl_pos < (ssize_t)ft_strlen(stash) -1)) 
	{
		remainder = ft_strdup(&stash[nl_pos + 1]);
		line = ft_substr(stash, 0, nl_pos + 1);
		if (!line || !remainder)
			return (clean_dangling(0, remainder, line));
		free(stash);
		stash = remainder;
		return (line);
	}
	line = ft_strdup(stash);
	return (free(stash), stash = NULL, line);
	//free(stash); 
	//stash = NULL;
	//return (line);
}
