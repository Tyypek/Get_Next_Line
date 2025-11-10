/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onoras <onoras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:37:14 by onoras            #+#    #+#             */
/*   Updated: 2025/11/10 17:25:04 by onoras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_strdup(const char *s)
{
	char	*str;
	int		size;

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
		if (!*stash || **stash == '\0')
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		str = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (str);
	}
	temp = ft_strdup(nptr + 1);
	str = ft_substr(*stash, 0, nptr - *stash + 1);
	free(*stash);
	*stash = temp;
	return (str);
}

char	*get_lines(int fd, char *stash, char *buf)
{
	ssize_t	temp;
	char	*cpystash;

	while (!ft_strchr(stash, '\n'))
	{
		temp = read(fd, buf, BUFFER_SIZE);
		if (temp == 0)
			break ;
		if (temp < 0)
			return (free(stash), stash = NULL, NULL);
		buf[temp] = '\0';
		cpystash = stash;
		stash = ft_strjoin(stash, buf);
		free(cpystash);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*stash;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	stash = get_lines(fd, stash, buf);
	result = get_rest(&stash);
	free(buf);
	if (stash && *stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	if (!result)
		stash = NULL;
	return (result);
}
