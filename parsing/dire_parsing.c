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

    i  = 1;
    while (line[i] && line[i] != ' ')
        i++;

    return i;
}

bool    check_path(char *line)
{
    int i;
    char *path;
    int fd;


    i = skip_ind_space(line);
    if (i == ft_strlen(line))
        return false;
    path = line+i;
    fd  = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("\n the file is't exist\n"); 
        return false;
    }
    return true;
}



bool check_line(char *line, t_direction *directions)
{

    if (ft_strncmp(line, "NO", 3))
    {
        directions->no_count++;
        if (check_path(line))
            return false;
    } 
    else if (ft_strncmp(line, "SO", 2))
    {
        directions->so_count++;
        if (check_path(line))
            return false;
    }
    else if (ft_strncmp(line, "WE", 2))
    {
        directions->we_count++;
        if (check_path(line))
            return false;
    }
    else if (ft_strncmp(line, "EA", 2))
    {
        directions->ea_count++;
        if (check_path(line))
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
    while (ft_strncmp(line, "\n", ft_strlen(line)))
    {
        free(line);
        line = get_next_line(fd); 
    }

    return line;
}

char **diretion_pasing(char *file_name)
{
    int fd;
    int i;
    char *line;
    char **lines;
    t_direction dire;

    line = NULL;
    
    fd = open_file(file_name, fd);
    if (fd == -1)
    {
        printf("\nError\nCannot open file\n");
        return NULL;
    }
    i = -1;
    while (++i)
    { 
        line = get_line(fd);
        if (!line)
            return lines;
        if (!check_line(line), &dire)
            return NULL;
        free(line);
    }
}
