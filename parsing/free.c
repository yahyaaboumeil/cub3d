#include "parsing.h"


void    free_memory(char **arr)
{
    int i;

    i = 0;
    while (arr && arr[i])
    {
        free(arr[i++]);
    }
    free(arr);
}

void    free_getline(int fd)
{
    char *line;

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

void    free_struct(t_data *data)
{
	free_memory(data->map);
	free(data->north_path);
	free(data->west_path);
	free(data->east_path);
	free(data->south_path);
}

void err_map(int fd, char *line, char **lines)
{
    printf("\nError\nYour map should have '1' in the start and at end\n");
    if (line)
        free(line);
    free_getline(fd);
    free_memory(lines);
    exit(1);
}
