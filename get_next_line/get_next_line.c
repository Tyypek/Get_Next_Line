/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onoras <onoras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:20:38 by onoras            #+#    #+#             */
/*   Updated: 2025/11/17 17:13:19 by onoras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_strdup(const char *s)
{
	char	*str;
	int		size;

	if (!s)
		return (NULL);
	size = ft_strlen(s) + 1;
	str = malloc(size);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, size);
	return (str);
}

char	*get_rest(char **stash)
{
	char	*str;
	char	*nptr;
	char	*temp;

	if (!*stash)
		return (NULL);
	nptr = ft_strchr(*stash, '\n');
	if (!nptr)
	{
		if (ft_strlen(*stash) == 0)
			return (free(*stash), *stash = NULL, NULL);
		str = ft_strdup(*stash);
		return (free(*stash), *stash = NULL, str);
	}
	temp = ft_strdup(nptr + 1);
	if (!temp)
		return (free(*stash), *stash = NULL, NULL);
	str = ft_substr(*stash, 0, nptr - *stash + 1);
	if (!str)
		return (free(temp), free(*stash), *stash = NULL, NULL);
	free(*stash);
	*stash = temp;
	return (str);
}

char	*get_lines(int fd, char **stash, char *buf)
{
	ssize_t	temp;
	char	*cpystash;

	temp = 1;
	while (!ft_strchr(*stash, '\n') && temp > 0)
	{
		temp = read(fd, buf, BUFFER_SIZE);
		if (temp == -1)
			return (free(*stash), *stash = NULL, NULL);
		buf[temp] = '\0';
		cpystash = *stash;
		*stash = ft_strjoin(*stash, buf);
		free(cpystash);
		if (!*stash)
			return (NULL);
	}
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	static char	*stash;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = get_lines(fd, &stash, buf);
	if (!stash)
		return (NULL);
	result = get_rest(&stash);
	if (ft_strlen(stash) == 0)
	{
		free(stash);
		stash = NULL;
	}
	return (result);
}

// #include <fcntl.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 1;
// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Line %d: %s", i, line); // line already contains '\n' if present
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
