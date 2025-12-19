/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:07:37 by yaboumei          #+#    #+#             */
/*   Updated: 2025/12/19 11:07:39 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_memory(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

void	free_getline(int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return ;
		free(line);
		line = NULL;
	}
}

void	free_struct(t_data *data, int free_map)
{
	if (data->north_path)
		free(data->north_path);
	if (data->west_path)
		free(data->west_path);
	if (data->east_path)
		free(data->east_path);
	if (data->south_path)
		free(data->south_path);
	if (free_map)
		free_memory(data->map);
	free(data);
}

void	clean(t_data *data, int fd, int free_map)
{
	free_struct(data, free_map);
	free_getline(fd);
}

void	err_map(int fd, char *line, char **lines)
{
	printf("\nError\nYour map should have '1' in the start and at end\n");
	if (line)
		free(line);
	free_getline(fd);
	free_memory(lines);
	exit(1);
}
