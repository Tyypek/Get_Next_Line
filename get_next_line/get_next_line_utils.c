/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onoras <onoras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:37:56 by onoras            #+#    #+#             */
/*   Updated: 2025/11/14 17:01:03 by onoras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if ((unsigned char)*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	srcsize;

	srcsize = 0;
	while (src[srcsize] != '\0')
		srcsize++;
	if (size == 0)
		return (srcsize);
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srcsize);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	cpylen;

	if (s == NULL)
		return (NULL);
	cpylen = ft_strlen(s);
	if (len > cpylen)
		len = cpylen;
	if (start >= cpylen)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (len > cpylen - start)
		len = cpylen - start;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (NULL);
	else if (!s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	j = 0;
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	while (i < len1)
	{
		new_str[i] = s1[i];
		i++;
	}
	while (j < len2)
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	return (new_str);
}

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*new_s;
// 	size_t	len1;
// 	size_t	len2;
// 	size_t	i;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	else if (!s1)
// 		return (ft_strdup(s2));
// 	else if (!s2)
// 		return ((char *)s1);
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	new_s = malloc((len1 + len2 + 1) * sizeof(*new_s));
// 	if (!new_s)
// 		return (free((char *)s1), NULL);
// 	i = -1;
// 	while (++i < len1)
// 		new_s[i] = s1[i];
// 	i = len1 - 1;
// 	while (++i < (len1 + len2))
// 		new_s[i] = s2[i - len1];
// 	new_s[len1 + len2] = 0;
// 	free((char *)s1);
// 	return (new_s);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*substr;
// 	size_t	s_length;

// 	if (!s)
// 		return (NULL);
// 	s_length = ft_strlen(s);
// 	if (s_length <= start)
// 		len = 0;
// 	else if (s_length < (len + start))
// 		len = s_length - start;
// 	substr = malloc((len + 1) * sizeof(*substr));
// 	if (!substr)
// 	{
// 		free((char *)s);
// 		return (NULL);
// 	}
// 	substr[len] = 0;
// 	while (len--)
// 		substr[len] = *(s + start + len);
// 	free((char *)s);
// 	return (substr);
// }
