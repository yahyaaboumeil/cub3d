/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:24:32 by yaboumei          #+#    #+#             */
/*   Updated: 2024/11/21 19:22:11 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//#include "get_next_line_utils.c"

char	*read_from_fd(int fd, char *record, char *s_line)
{
	char	*temp;
	ssize_t	size_bu;

	while (1)
	{
		size_bu = read(fd, record, BUFFER_SIZE);
		if (size_bu <= 0)
			break ;
		record[size_bu] = 0;
		if (!s_line)
			s_line = ft_substr("", 0, 0);
		temp = ft_strjoin(s_line, record);
		free(s_line);
		s_line = temp;
		if (ft_strchr(record, '\n'))
			return (s_line);
	}
	return (s_line);
}

char	*split_at_new_line(char **s_line)
{
	char	*temp;
	char	*record;
	int		pos;

	pos = 0;
	while ((*s_line)[pos] && (*s_line)[pos] != '\n')
		pos++;
	if ((*s_line)[pos] == '\n')
	{
		record = ft_substr(*s_line, 0, ++pos);
		temp = *s_line;
		if ((*s_line)[pos] == '\0')
		{
			free(*s_line);
			*s_line = NULL;
			return (record);
		}
		*s_line = ft_substr(temp, pos, ft_strlen(temp));
		free(temp);
		return (record);
	}
	record = ft_substr(*s_line, 0, ft_strlen(*s_line));
	free(*s_line);
	*s_line = NULL;
	return (record);
}

char	*get_next_line(int fd)
{
	static char	*s_line = NULL;
	char		*record;
	char		*line;

	if (fd < 0)
		return (NULL);
	record = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!record)
	{
		if (s_line)
			free(s_line);
		return (NULL);
	}
	s_line = read_from_fd(fd, record, s_line);
	free(record);
	if (!s_line)
		return (NULL);
	line = split_at_new_line(&s_line);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char *str;
	int	i;

	fd = open("test.txt", O_RDWR);
	//if (fd == -1)
		//return (1);
	// for(int i = 0; i < 1; i++)
	i = 0;
	printf("%d", fd);
	while ((str = get_next_line(fd)) != NULL)
	{
		// str = get_next_line(fd);
		printf("%d %s", i++, str);
		free(str);
	}
	close(fd);
	return (0);
}*/
