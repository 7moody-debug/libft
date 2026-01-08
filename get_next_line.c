	#include "get_next_line.h"

	static char	*read_and_store(int fd, char *stash)
	{
		char	*buffer;
		ssize_t	bytes;

		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		bytes = 1;
		while (!ft_strchr(stash, '\n') && bytes > 0)
		{
			bytes = read(fd, buffer, BUFFER_SIZE);
			if (bytes == -1)
			{
				free(buffer);
				free(stash);
				return (NULL);
			}
			buffer[bytes] = '\0';
			stash = ft_strjoin(stash, buffer);
			if (!stash)
			{
				free(buffer);
				return (NULL);
			} 	 	
		}
		free(buffer);
		return (stash);
	}

	static char	*extract_line(char *stash)
	{
		char	*line;
		size_t	i = 0;

		if (!stash || !stash[0])
			return (NULL);
		while (stash[i] && stash[i] != '\n')
			i++;
		line = malloc(i + 2);
		if (!line)
			return (NULL);
		i = 0;
		while (stash[i] && stash[i] != '\n')
		{
			line[i] = stash[i];
			i++;
		}
		if (stash[i] == '\n')
			line[i++] = '\n';
		line[i] = '\0';
		return (line);
	}

	static char	*clean_stash(char *stash)
	{
		char	*new_stash;
		size_t	i = 0;
		size_t	j = 0;

		while (stash[i] && stash[i] != '\n')
			i++;
		if (!stash[i])
		{
			free(stash);
			return (NULL);
		}
		new_stash = malloc(ft_strlen(stash) - i);
		if (!new_stash)
		{
			free(stash);
			return (NULL);
		}
		i++;
		while (stash[i])
			new_stash[j++] = stash[i++];
		new_stash[j] = '\0';
		free(stash);
		return (new_stash);
	}

	char	*get_next_line(int fd)
	{
		static char	*stash;
		char		*line;

		if (fd < 0 || BUFFER_SIZE <= 0)
			return (NULL);
		stash = read_and_store(fd, stash);
		if (!stash)
			return (NULL);
		line = extract_line(stash);
		stash = clean_stash(stash);
		return (line);
	}
