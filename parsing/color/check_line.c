/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:08:37 by yaboumei          #+#    #+#             */
/*   Updated: 2025/12/19 11:08:39 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static bool	check_rgb_value(char *str)
{
	int	value;

	if (*(str + (ft_strlen(str) - 1)) == '\n')
		*(str + (ft_strlen(str) - 1)) = 0;
	if (!is_number(str))
		return (false);
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		return (false);
	return (true);
}

static t_data	*save_color(t_data *data, char type, t_count *count, char *line)
{
	char	**split;

	split = NULL;
	if (type == 'f')
	{
		if (count->count_f != 1)
			return (NULL);
		split = ft_split(ft_strchr(line, 'F'), ',');
		data->f_color[0] = atoi(split[0]);
		data->f_color[1] = atoi(split[1]);
		data->f_color[2] = atoi(split[2]);
	}
	else
	{
		if (count->count_c != 1)
			return (NULL);
		split = ft_split(ft_strchr(line, 'C'), ',');
		data->c_color[0] = atoi(split[0]);
		data->c_color[1] = atoi(split[1]);
		data->c_color[2] = atoi(split[2]);
	}
	free_memory(split);
	return (data);
}

bool	norm_check_line2(t_data *data, t_check_line *help, char *line,
		t_count *count)
{
	data = save_color(data, help->type, count, line);
	if (!data)
		return (free_split(help->split), false);
	return (free_split(help->split), true);
}

bool	check_line2(t_data *data, char *line, t_count *count_color)
{
	t_check_line	help;

	if (!line)
		return (false);
	while (*line == ' ')
		line++;
	if (*line == 'F')
		(1) && (count_color->count_f++, help.content = line + 1,
			help.type = 'f', help.parts = 0);
	else if (*line == 'C')
		(1) && (count_color->count_c++, help.content = line + 1,
			help.type = 'c', help.parts = 0);
	else
		return (false);
	while (*help.content == ' ')
		help.content++;
	help.split = ft_split(help.content, ',');
	while (help.split && help.split[help.parts])
		help.parts++;
	if (help.parts != 3 || !check_rgb_value(help.split[0])
		|| !check_rgb_value(help.split[1]) || !check_rgb_value(help.split[2]))
		return (printf("Error\nInvalid color format: %s\n", line),
			free_split(help.split), false);
	return (norm_check_line2(data, &help, line, count_color));
}
