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
	free(temp);
	return (stash);
}
char	*read_buff(int fd, char *stash)
{
	ssize_t bytes = 1;
	char *buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (bytes)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		// Erro a ler
		if (bytes < 0)
			return(clean_dangling(buffer, stash, NULL));
		buffer[bytes] = '\0';
		// Fim do ficheiro
		if (!bytes) // || bytes < BUFFER_SIZE)
			break ;
		stash = build_buffer(stash, buffer);
		if (ft_chrpos(stash, '\n') > -1)
			break ;
		// Confirmar se stash nao foi mal alocada
	}
	free(buffer);
	return (stash);
}
/*char *update_stash(char *stash)
{
	char		*new_stash;
	int 		i = 0;
	int			new = 0;
	
	if (!stash)
		return (NULL);
//chego ao \n
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	int len = 0;
//agora o i vai contar a proxima linha
	while (stash[len + i] && stash[len + i] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
// limpar a stash e dar-lhe o remainder
	//free(stash);
	new_stash = malloc(sizeof(char) * (len + 1));
	if (!new_stash)
		return(NULL);
	while (stash[i])
		new_stash[new++] = stash[i++];
	new_stash[new] = '\0';
	free(stash);
	return (new_stash);
}
char *fetch_line(char *stash, char *line)
{
	int i = 0;
	int nl = 0;
//line deveria sempre estar null, pois e atribuido null no inicio de getnextline
//mas stash pode conter apenas o \0 ou ter algum problema
	if (!stash)
		return (NULL);
//ja atribuo a line os char ate /n
	//if (!ft_strchr(stash, '\n'))
	//	return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i * sizeof(char) + 1);
	if (!line)
		return (NULL);
// <= para nao ignorar o \n 
	while(nl <= i)
	{
		line[nl] = stash[nl];
		nl++;
	}
	line[nl] = '\0';
	return (line);
}*/

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
		clean_dangling(stash, NULL, NULL);
	stash = read_buff(fd, stash);
	if (!stash)
		return(clean_dangling(stash, NULL, NULL));
	nl_pos = ft_chrpos(stash, '\n');
	if (nl_pos != -1 && nl_pos < (ssize_t)ft_strlen(stash) - 1) 
	{
		remainder = ft_strdup(&stash[nl_pos + 1]);
		line = ft_substr(stash, 0, nl_pos + 1);
		if (!line || !remainder)
			return (clean_dangling(stash, remainder, line));
		free(stash);
		stash = remainder;
		return (line);
	}
	line = ft_strdup(stash);
	return (free(stash), stash = NULL, line);
	// Tens que perceber se ha algum remainder.
	// Se houver tens que o guardar, e enviar a nova linha
	// Nao esquecer se nao houver remainder para dar free a stash e definir NULL
	//line = fetch_line(stash, line);
	//stash = update_stash(stash);
	//stash = NULL;


	return (line);
}

/*#include <stdio.h>
#include <fcntl.h>

int main()
{
	char *line = "";
	int fd = open("test.txt", O_RDONLY);


	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
}*/