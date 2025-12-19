/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:17:33 by yaboumei          #+#    #+#             */
/*   Updated: 2025/12/15 12:23:25 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void	norm_free(int fd, char *line, char **lines)
{
	free(line);
	free_getline(fd);
	free_memory(lines);
}

bool	check_last_line(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

char	**check_err(int fd, t_counters counters, char *line, char **lines)
{
	if (counters.count_err == -1)
	{
		printf("\nError\nmap has error\n");
		return (norm_free(fd, line, lines), NULL);
	}
	if (counters.count_p != 1)
	{
		if (counters.count_p == 0)
			printf("\nError\nNo starting position (N/S/W/E) in map\n");
		else
			printf("\nError\nMultiple starting positions (N/S/W/E) in map\n");
		return (norm_free(fd, line, lines), NULL);
	}
	if (!check_last_line(line))
	{
		printf("\nError\nlast line isn't valid\n");
		return (norm_free(fd, line, lines), NULL);
	}
	if (line)
		free(line);
	return (lines);
}


char	**check_first_line(int fd, char **lines)
{
	int		i;
	char	*line;

	line = get_line(fd);
	if (line == NULL)
		return (NULL);
	i = skip_espas(line);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			i++;
			return (norm_free(fd, line, lines), NULL);
		}
		i++;
	}
	lines = add_line(line, lines);
	if (!lines)
		return (norm_free(fd, line, lines), NULL);
	free(line);
	return (lines);
}

char	**help(char **lines, char **line, int fd)
{
	lines = check_first_line(fd, lines);
	if (!lines)
	{
		printf("\nError\nThe first line isn't correct\n");
		exit(1);
	}
	*line = get_line(fd);
	return (lines);
}

char	**check_input(int fd, char **lines)
{
	int			i;
	char		*line;
	char		*temp;
	t_counters	counters;

	i = 0;
	counters = init(&counters);
	lines = help(lines, &line, fd);
	while (true)
	{
		if (!check_map_line(fd, line, &counters, lines))
			break ;
		lines = add_line(line, lines);
		temp = get_line(fd);
		if (temp == NULL)
			break ;
		if (line)
			free(line);
		line = temp;
		i++;
	}
	return (check_err(fd, counters, line, lines));
}
