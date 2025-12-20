/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:16:28 by yaboumei          #+#    #+#             */
/*   Updated: 2025/12/19 11:16:29 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	**check_count(char **lines, t_direction dire)
{
	if (dire.no_count != 1)
		return (NULL);
	if (dire.ea_count != 1)
		return (NULL);
	if (dire.we_count != 1)
		return (NULL);
	if (dire.so_count != 1)
		return (NULL);
	return (lines);
}

bool	check_path(char *line)
{
	int		i;
	int		fd;
	char	*path;

	path = NULL;
	i = skip_ind_space(line);
	if (i == (int)ft_strlen(line))
		return (false);
	if (*(line + ft_strlen(line) - 1) == '\n')
		*(line + ft_strlen(line) - 1) = 0;
	path = line + i;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nthe file is't exist\n"), false);
	close(fd);
	return (true);
}

static bool	norm(t_data *data, int i, char *line, t_direction *directions)
{
	if (!ft_strncmp(line + i, "WE", 2))
	{
		directions->we_count++;
		if (!check_path(line + i) || (directions->we_count > 1))
			return (false);
		data->west_path = ft_strdup(line + skip_ind_space(line));
	}
	else if (!ft_strncmp(line + i, "EA", 2))
	{
		directions->ea_count++;
		if (!check_path(line + i) || (directions->ea_count > 1))
			return (false);
		data->east_path = ft_strdup(line + skip_ind_space(line));
	}
	else
		return (false);
	return (true);
}

bool	check_line(t_data *data, char *line, t_direction *directions)
{
	int	i;

	i = 0;
	if (!line)
		return (false);
	while (line[i++] == ' ')
		;
	if (i-- == (int)ft_strlen(line))
		return (false);
	if (!ft_strncmp(line + i, "NO", 2))
	{
		if (!check_path(line + i) || (++directions->no_count > 1))
			return (false);
		data->north_path = ft_strdup(line + skip_ind_space(line));
	}
	else if (!ft_strncmp(line + i, "SO", 2))
	{
		directions->so_count++;
		if (!check_path(line + i) || (directions->so_count > 1))
			return (false);
		data->south_path = ft_strdup(line + skip_ind_space(line));
	}
	else if (!norm(data, i, line, directions))
		return (false);
	return (true);
}
