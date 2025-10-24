/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:25:14 by yaboumei          #+#    #+#             */
/*   Updated: 2024/11/17 20:54:34 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return 0;
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	le_src;

	i = 0;
	le_src = ft_strlen(src);
	if (size == 0)
		return (le_src);
	while (src[i] && (size - 1 > i))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (le_src);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	le;

	if (s == NULL)
		return (NULL);
	le = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (start > le)
	{
		ptr = malloc(sizeof(char *));
		if (!ptr)
			return (NULL);
		ptr[0] = 0;
		return (ptr);
	}
	if ((le - start) < len)
		len = le - start;
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, (s + start), len + 1);
	return (ptr);
}
