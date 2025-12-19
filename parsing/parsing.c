/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:13:59 by yaboumei          #+#    #+#             */
/*   Updated: 2025/12/15 11:52:52 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	save_player_pos(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->map[i])
	{
		while (d->map[i][j])
		{
			if (d->map[i][j] == 'N' || d->map[i][j] == 'S'
				|| d->map[i][j] == 'W' || d->map[i][j] == 'E')
			{
				d->x = i;
				d->y = j;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	save_width_height(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i][j++])
		;
	data->width = j;
	while (data->map[i++])
		;
	data->hight = i;
}

t_data	*init_struct(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->map = NULL;
	data->north_path = NULL;
	data->west_path = NULL;
	data->east_path = NULL;
	data->south_path = NULL;
	data->x = 0;
	data->y = 0;
	data->width = 0;
	data->hight = 0;
	data->map = NULL;
	return (data);
}

static t_data	*normin(t_data *data, int fd)
{
	data->map = NULL;
	data->map = check_input(fd, data->map);
	if (!data->map)
		return (clean(data, fd, false), NULL);
	save_player_pos(data);
	save_width_height(data);
	if (!check_if_can_play_in_map(data->map))
		return (printf("\nError\nthe map is not suitable for play\n"),
			clean(data, fd, true), NULL);
	return (data);
}

t_data	*parsing(char *file_name)
{
	t_norm		norm;
	char		*line;
	t_direction	directions;
	t_count		count;
	t_data		*data;

	(1) && (count.count_f = 0, count.count_c = 0, data = NULL, norm.fd = 0);
	data = init_struct(data);
	norm.i = 0;
	if (!check_file(file_name))
		return (printf("\nError\nthe file should be file.cub\n"), NULL);
	norm.fd = open_file(file_name, norm.fd);
	if (norm.fd == -1)
		return (printf("\nError\nCannot open file\n"), NULL);
	while (norm.i++ < 6)
	{
		line = get_line(norm.fd);
		if (!check_line(data, line, &directions))
			if (!check_line2(data, line, &count))
				return (printf("Error\nthere is err in the path or color line\n"),
					clean(data, norm.fd, false), free(line), NULL);
		free(line);
	}
	return (normin(data, norm.fd));
}
