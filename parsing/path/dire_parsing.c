#include "../parsing.h"
void    init_struct2(t_direction *dire)
{

    dire->no_count = 0;
    dire->ea_count = 0;
    dire->we_count = 0;
    dire->so_count = 0;
}


char *get_line(int fd)
{
    char *line;

    line = get_next_line(fd);
    if (!line)
        return line;
    while (line && !ft_strncmp(line, "\n", ft_strlen(line)))
    {
        free(line);
        line = get_next_line(fd); 
    }

    return line;
}

static char **full_arr(int fd, char **lines ,t_direction *dire, int i)
{
    char *line;
   
    while (++i < 5)
    { 
        line = get_line(fd);
        if (!line)
            break;
        if (!check_line(line, &*dire))
            return (free(line), free_memory(lines), free_getline(fd), NULL); 
        lines[i-1] = cpy_line(line);
        lines[i] = NULL;
        free(line);
    }
    return lines;
}

char **diretion_pasing(int fd)
{
    int i;
    char **lines;
    t_direction dire;

    i = 0;
    init_struct2(&dire);
    lines = malloc((sizeof(char*) * 5));
    if (!lines)
        return NULL;
    lines = full_arr(fd, lines,&dire, i);
    if (!check_count(lines, dire))
        return (free_memory(lines),free_getline(fd),NULL);
    return (lines);
}
