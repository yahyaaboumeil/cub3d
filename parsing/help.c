#include "parsing.h"

t_counters init(t_counters *counters)
{
    counters->count_p = 0;
    counters->count_err = 0;
    return *counters;
}

int count(char **lines)
{
    int i = 0;
    if (!lines)
        return 0;
    while (lines[i])
        i++;
    return i;
}

int skip_espas(char *line)
{
    int i = 0;
    if (!line)
        return 0;
    while (line[i] && line[i] == ' ')
        i++;
    return i;
}

/*void free_struct(t_data *data)
{
	free_memory(data->map);
	free(data->north_path);
	free(data->west_path);
	free(data->south_path);
	free(data->east_path);
	free(data);
}*/

char **add_line(char *line, char **lines)
{
    char **new;
    int i;

    i = 0;
    new = malloc(sizeof(char *) * (count(lines)+ 2));
    if (new == NULL)
        return NULL;
    while (lines[i])
    {
        new[i] = ft_strdup(lines[i]);
        i++;
    }
    new[i] = ft_strdup(line); /* copy added line */
    if (!new[i])
    {
        while (--i >= 0)
            free(new[i]);
        free(new);
        return NULL;
    }
    i++;
    new[i] = NULL;
    free_memory(lines);
    return new;
}
