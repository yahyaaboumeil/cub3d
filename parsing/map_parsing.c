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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* --- helpers --- */

bool check_last_line(char *line)
{
    int i;

    if (!line)
        return false;

    i = 0;
    /* skip leading spaces */
    while (line[i] && line[i] == ' ')
        i++;

    /* from first non-space until newline or end, all chars should be '1' */
    while (line[i] && line[i] != '\n')
    {
        if (line[i] != '1' && line[i] != ' ')
            return false;
        i++;
    }
    return true;
}

char **check_err(int fd, t_counters counters, char *line, char **lines)
{
    if (counters.count_err == -1)
    {
        printf("\nError\nmap has error\n");
		free(line);
        free_getline(fd);
        free_memory(lines);
        return NULL;
    }
    if (counters.count_p != 1)
    {
        if (counters.count_p == 0)
            printf("\nError\nNo starting position (N/S/W/E) in map\n");
        else
            printf("\nError\nMultiple starting positions (N/S/W/E) in map\n");
		free(line);
        free_getline(fd);
        free_memory(lines);
        return NULL;
    }
    if (!check_last_line(line))
    {
        printf("\nError\nlast line isn't valid\n");
		free(line);
        free_getline(fd);
        free_memory(lines);
        return NULL;
    }
    if (line)
        free(line);
    return lines;
}

/*void err_map(int fd, char *line, char **lines)
{
    printf("\nError\nYour map should have '1' in the start and at end\n");
    if (line)
        free(line);
    free_getline(fd);
    free_memory(lines);
    exit(1);
}*/


/*bool check_map_line(int fd, char *line, t_counters *counters, char **lines)
{
    int i;
    int end;

    if (line == NULL)
        return false;
    i = skip_espas(line);
    end = last_non_newline_index(line);
    if (end < 0)
        err_map(fd, line, lines);
    if (line[i] != '1' || line[end] != '1')
        err_map(fd, line, lines);
    while (line[i] && line[i] != '\n')
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
        {
            if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
                counters->count_p++;
            else 
               return (counters->count_err = -1, false);
        }
        i++;
    }
    return true;
}*/


char **check_first_line(int fd, char **lines)
{
    char *line;
    int i;

    line = get_line(fd);
    if (line == NULL)
        return NULL;
    i = skip_espas(line);
    while (line[i] && line[i] != '\n')
    {
        if (line[i] != '1' && line[i] != ' ')
        {
            i++;
            free_memory(lines);
            free(line);
            free_getline(fd);
            return NULL;
        }
        i++;
    }
    lines = add_line(line, lines);
    if (!lines)
    {
	    free(line);
	    free_getline(fd);
	    free_memory(lines);
	    return NULL;
    }
    free(line);
    return lines;
}

char **help(char **lines, char **line, int fd)
{
	lines = check_first_line(fd, lines);
    if (!lines)
    {
        printf("\nError\nThe first line isn't correct\n");
        exit(1);
    }
    *line = get_line(fd);
    return lines;
}


char **check_input(int fd, char **lines)
{
	int i;
	char *line;
	char *temp;
	t_counters counters;

	i = 0;
	counters = init(&counters);
	lines = help(lines, &line, fd); /* adds the first map line internally */
	while (true)
	{
		if (!check_map_line(fd, line, &counters, lines))
		    break;
		lines = add_line(line, lines);
		temp = get_line(fd);
		if (temp == NULL)
		    break;
		if (line)
		    free(line);
		line = temp;
		i++;
	}
	return check_err(fd, counters, line, lines);
}

