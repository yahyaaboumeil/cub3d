/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:07:56 by yaboumei          #+#    #+#             */
/*   Updated: 2025/12/19 11:08:08 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_counters	init(t_counters *counters)
{
	counters->count_p = 0;
	counters->count_err = 0;
	return (*counters);
}

int	count(char **lines)
{
	int	i;

	i = 0;
	if (!lines)
		return (0);
	while (lines[i])
		i++;
	return (i);
}

int	skip_espas(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

char	**add_line(char *line, char **lines)
{
	char	**new;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	new = malloc(sizeof(char *) * (count(lines) + 2));
	if (new == NULL)
		return (NULL);
	while (lines && lines[i])
	{
		new[i] = ft_strdup(lines[i]);
		i++;
	}
	new[i] = ft_strdup(line + j);
	if (!new[i])
	{
		while (--i >= 0)
			free(new[i]);
		free(new);
		return (NULL);
	}
	i++;
	new[i] = NULL;
	free_memory(lines);
	return (new);
}

void	norm_free(int fd, char *line, char **lines)
{
	free(line);
	free_getline(fd);
	free_memory(lines);
}
