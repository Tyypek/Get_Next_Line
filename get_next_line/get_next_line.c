/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onoras <onoras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:37:14 by onoras            #+#    #+#             */
/*   Updated: 2025/11/11 17:20:16 by onoras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	nptr = ft_strchr(*stash, '\n');
	if (!nptr)
	{
		if (**stash == '\0')
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

char	*get_lines(int fd, char *stash, char *buf)
{
	ssize_t	temp;
	char	*cpystash;

	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	while (!ft_strchr(stash, '\n'))
	{
		temp = read(fd, buf, BUFFER_SIZE);
		if (temp == 0)
			break ;
		if (temp == -1)
			return (free(stash), stash = NULL, NULL);
		buf[temp] = '\0';
		cpystash = stash;
		if (stash && buf)
			stash = ft_strjoin(stash, buf);
		if (!stash)
			return (free(cpystash), NULL);
		free(cpystash);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*stash = NULL;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	stash = get_lines(fd, stash, buf);
	if (!stash)
		return (free(buf), NULL);
	result = get_rest(&stash);
	if (stash && *stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	return (free(buf), result);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 1;
	
// 	fd = open("multiple_nl.txt", O_RDONLY);
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
