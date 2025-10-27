/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:17:33 by yaboumei          #+#    #+#             */
/*   Updated: 2025/02/26 20:17:35 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	check_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i++] != '1')
		{
			free(line);
			return (false);
		}
	}
	return (true);
}

void	err_map(int fd,char *line, char **lines)
{
	printf("\nError\nYour map should have '1' in the start and at end\n");
	free(line);
	free_getline(fd);
	free_memory(lines);
	exit(1);
}

int	skip_espas(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return i;
}

bool	check_map_line(int fd,char *line, t_counters *counters, char **lines)
{
	int	i;
	int	len;

	if (line == NULL)
		return (false);
	(1) && (i = 0, len = ft_strlen(line));
	i = skip_espas(line);
	if (line[i] != '1' || line[len - 2] != '1')
		err_map(fd, line, lines);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0')
		{
			if (line[i] == 'P')
				counters->count_p++;
			else if (line[i] == 'C')
				counters->count_c++;
			else if (line[i] == 'E')
				counters->count_e++;
			else
				return (counters->count_err = -1);
		}
		i++;
	}
	return (true);
}

// char	*get_map(char *line1, char *line2)
// {
// 	char	*new_line;

// 	if (line1[0] == 0)
// 	{
// 		line1 = malloc(sizeof(char));
// 		line1[0] = 0;
// 	}
// 	if (line2 == NULL)
// 		return (NULL);
// 	new_line = ft_strjoin(line1, line2);
// 	if (new_line == NULL)
// 		return (NULL);
// 	free(line1);
// 	return (new_line);
// }

char	**check_err(int fd, t_counters counters, char *line,
		char **lines)
{
	if (counters.count_err == -1 || counters.count_c < 1)
	{
		printf("\nError\nmap has error\n");
		free(line);
		free_getline(fd);
		free_memory(lines);
		return (NULL);
	}
	if (counters.count_p != 1 || counters.count_e != 1)
	{
		printf("\nError\nThe (E OR P) are duplicate in map\n");
		if (line)
			free(line);
		free_getline(fd);
		free_memory(lines);
		return (NULL);
	}
	if (!check_last_line(line))
	{
		printf("\nError\nlast line is't good\n");
		free_memory(lines);
		return (NULL);
	}
	free(line);
	return (lines);
}


int count(char **lines)
{
    int i;

    i = 0;
    while (lines[i])
        i++;
    return i;
}

char **add_line(char *line, char **lines)
{
    char **new;
    int i;

    i = -1;
    new = malloc((sizeof(char *) * count(lines)) + 1);
    if (new == NULL)
        return NULL;
    while (lines[++i])
        new[i] = lines[i];
    new[i++] = ft_strdup(line);
    new[i] = NULL;
	return new;
}



bool	check_first_line(int fd, char **lines)
{
	char	*line;
	int		i;

	i = 0;
	line = get_line(fd);
	if (line == NULL)
		return (false);
    i = skip_espas(line);
	while (line[i] && line[i] != '\n')
	{
		if (line[i++] != '1')
		{
			free_memory(lines);
			free(line);
			free_getline(fd);
			return (false);
		}
	}
    lines = add_line(line, lines); 
	free(line);
	return (true);
}

char **help(char **lines, char **line, int fd)
{
	if (!check_first_line(fd, lines))
	{
		printf("\nError\nThe first line is't correct\n");
		exit(1);
	}
	*line = get_line(fd);
	return lines;
}
t_counters	init(t_counters *counters)
{
	counters->count_c = 0;
	counters->count_e = 0;
	counters->count_p = 0;
	counters->count_err = 0;

	return *counters;
}

char	**check_input(int fd, char **lines)
{
	char	*line;
	char	*temp;
	int	i;
	t_counters counters;

	counters =  init(&counters);
	i = 6;
	lines = help(lines, &line, fd);
	while (++i)
	{
		if (!check_map_line(fd, line, &counters, lines))
			break ;
		lines[i] = ft_strdup(line);
		temp = get_line(fd);
		if (temp == NULL)
			break ;
		if (line)
			free(line);
		line = temp;
	}
	return (check_err(fd, counters, line, lines));

}
