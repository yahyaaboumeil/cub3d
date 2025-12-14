#include "parsing.h"

typedef struct s_dire_parsing
{
    int no_count;
    int so_count;
    int we_count;
    int ea_count;

} t_direction;


int open_file(char *file_name, int fd)
{
    fd = open(file_name, O_RDONLY);
    return fd; 
}

int skip_ind_space(char *line)
{
    int i;

    i  = 2;
    while (line[i] && line[i] == ' ')
        i++;

    return i;
}

bool    check_path(char *line)
{
    int i;
    int fd;
    char *path;

    path = NULL;
    i = skip_ind_space(line);
    if (i == (int)ft_strlen(line))
        return false;
    if (*(line+ft_strlen(line)-1) == '\n')
        *(line+ft_strlen(line)-1) = 0;
    path = line+i;
    fd  = open(path, O_RDONLY);
    if (fd == -1)
        return (printf("\n the file is't exist\n"), false); 
    return true;
}



bool check_line(char *line, t_direction *directions)
{

    if (!ft_strncmp(line, "NO", 2))
    {
        directions->no_count++;
        if (!check_path(line))
            return false;
    } 
    else if (!ft_strncmp(line, "SO", 2))
    {
        directions->so_count++;
        if (!check_path(line))
            return false;
    }
    else if (!ft_strncmp(line, "WE", 2))
    {
        directions->we_count++;
        if (!check_path(line))
            return false;
    }
    else if (!ft_strncmp(line, "EA", 2))
    {
        directions->ea_count++;
        if (!check_path(line))
            return false;
    }
    else
        return false;
    return true;
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

char **check_count(char **lines, t_direction dire)
{

    if (dire.no_count > 1)
        return NULL;
    if (dire.ea_count > 1)
        return NULL;
    if (dire.we_count > 1)
        return NULL;
    if (dire.so_count > 1)
        return NULL;

    return lines;
}

static  void    init_struct(t_direction *dire, char **line)
{

    i = 0;
    line = NULL
    dire->no_count = 0;
    dire->ea_count = 0;
    dire->we_count = 0;
    dire->so_count = 0;
}



char **diretion_pasing(char *file_name)
{
    int i;
    int fd = 0;
    char *line;
    char **lines;
    t_direction dire;

    lines = &line;
    init_struct(&dire, &line, &i);
    fd = open_file(file_name, fd);
    if (fd == -1)
        return (printf("\nError\nCannot open file\n"), NULL);
    while (++i)
    { 
        line = get_line(fd);
        if (!line)
            break;
        if (!check_line(line, &dire))
            return NULL;
        free(line);
    }
    return (check_count(lines, dire));
}

