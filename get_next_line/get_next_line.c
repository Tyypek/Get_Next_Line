/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onoras <onoras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:37:14 by onoras            #+#    #+#             */
/*   Updated: 2025/11/13 18:50:50 by onoras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	get_rest(char *line)
{
	char	*newline;

	if (!line)
		return ;
	newline = ft_strchr(line, '\n');
	if (!newline)
	{
		*line = 0;
		return ;
	}
	newline++;
	ft_strlcpy(line, newline, BUFFER_SIZE);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*result;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	read_bytes = 1;
	result = ft_strjoin(NULL, stash);
	*stash = 0;
	while (!ft_strchr(stash, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, stash, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(result), *stash = 0, NULL);
		stash[read_bytes] = '\0';
		result = ft_strjoin(result, stash);
		if (!result)
			return (NULL);
	}
	if (!read_bytes && !*result)
		return (free(result), NULL);
	if (ft_strchr(result, '\n'))
		result = ft_substr(result, 0, ft_strchr(result, '\n') - result + 1);
	get_rest(stash);
	return (result);
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
