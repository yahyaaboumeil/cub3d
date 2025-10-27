#include "color.h"

static  void    init_struct(t_count *count)
{

    count->count_c = 0;
    count->count_f = 0;
}

char    **cpy_lines(char **lines, char **new_lines)
{
    int i;
    
    i = -1;
    while (lines[++i])
        new_lines[i] = ft_strdup(lines[i]);
    new_lines[i]  = NULL;
    free_memory(lines);
    return new_lines;
}

static char **full_arr(char **lines, int fd, t_count *count, int i)
{
    char *line;

    while (++i < 7)
    {
        line = get_line(fd);
        if (!line)
            break;
        if (!check_line(line, count)) 
            return (free(line),free_getline(fd) ,free_memory(lines), NULL);
        lines[i-1] = cpy_line(line);
        lines[i] =  NULL;
        free(line);
    }
    return lines;
}

char **color_parsing(char **old_lines, int fd)
{
    char **lines;
    t_count count;
    int i;
    
    i = 4;
    init_struct(&count);
    lines = malloc(sizeof(char *) * 7);
    lines = cpy_lines(old_lines, lines);
    lines = full_arr(lines, fd, &count, i);
    if (!lines)
        return NULL;
    if (count.count_c != 1 || count.count_f != 1)
        return (free_memory(lines), free_getline(fd),NULL);
    return lines;
}
