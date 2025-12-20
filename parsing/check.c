/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:07:26 by yaboumei          #+#    #+#             */
/*   Updated: 2025/12/19 11:07:30 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	check_file(char *file)
{
	char	*pos;

	pos = ft_strnstr(file, ".cub", ft_strlen(file));
	if (pos == NULL)
		return (false);
	if (file == pos)
		return (false);
	if (ft_strncmp(".cub", pos, ft_strlen(pos)))
		return (false);
	return (true);
}

bool	check_if_can_play_in_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j
					- 1] == ' ' || map[i][j + 1] == ' ')
					return (false);
				if (j > (int)ft_strlen(map[i - 1]) || j > (int)ft_strlen(map[i
							+ 1]))
					return (false);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (true);
}

bool	check_map_line(int fd, char *line, t_counters *counters, char **lines)
{
	int	i;
	int	end;

	if (line == NULL)
		return (false);
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
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
				|| line[i] == 'E')
				counters->count_p++;
			else
				return (counters->count_err = -1, false);
		}
		i++;
	}
	return (true);
}

int	last_non_newline_index(const char *line)
{
	int	len;

	if (!line)
		return (-1);
	len = ft_strlen(line);
	if (len == 0)
		return (-1);
	len--;
	while (len >= 0 && (line[len] == '\n' || line[len] == '\r'
			|| line[len] == ' '))
		len--;
	return (len);
}
