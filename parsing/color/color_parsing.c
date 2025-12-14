#include "color.h"

static void init_struct(t_count *count)
{
    count->count_c = 0;
    count->count_f = 0;
}

static char **cpy_lines(char **src, char **dst)
{
    int i = 0;

    if (!src || !dst)
        return NULL;

    while (src[i])
    {
        dst[i] = ft_strdup(src[i]);
        if (!dst[i])
            return free_memory(dst), NULL;
        i++;
    }
    dst[i] = NULL;
    free_memory(src);
    return dst;
}

static char **full_arr(char **lines, int fd, t_count *count, int start)
{
    char *line;
    int i = start;

    while (i < 6)      
    {
        line = get_line(fd);
        if (!line)
            return free_getline(fd), free_memory(lines), NULL;

        if (!check_line2(line, count))
            return free(line), free_getline(fd), free_memory(lines), NULL;

        lines[i] = ft_strdup(line);
        free(line);

        if (!lines[i])
            return free_memory(lines), free_getline(fd), NULL;

        i++;
        lines[i] = NULL;
    }

    return lines;
}

char **color_parsing(char **old_lines, int fd)
{
    char **lines;
    t_count count;

    init_struct(&count);
    lines = malloc(sizeof(char *) * 7);
    if (!lines)
        return NULL;
    lines = cpy_lines(old_lines, lines);
    if (!lines)
        return NULL;
    lines = full_arr(lines, fd, &count, 4);
    if (!lines)
        return NULL;
    if (count.count_c != 1 || count.count_f != 1)
        return free_memory(lines), free_getline(fd), NULL;
    return lines;
}

