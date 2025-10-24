/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:16:28 by yaboumei          #+#    #+#             */
/*   Updated: 2025/02/26 20:16:30 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

static size_t	is_find(const char *big, const char *little, size_t pos,
		size_t len)
{
	size_t	i;

	i = 0;
	while (big[pos] && little[i] && len > pos)
	{
		if (big[pos] != little[i])
			return (i);
		pos++;
		i++;
	}
	return (i);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			if (ft_strlen(little) == is_find(big, little, i, len))
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((s1[i] || s2[i])))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
