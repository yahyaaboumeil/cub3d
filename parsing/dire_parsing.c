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



static bool check_line(char *line, t_direction *directions)
{

    int i;

    i = 0;
    while (line[i++] == ' ');
    if (i-- == (int)ft_strlen(line))
        return true;
    
    if (!ft_strncmp(line+i, "NO", 2))
    {
        directions->no_count++;
        if (!check_path(line+i))
            return false;
    } 
    else if (!ft_strncmp(line+i, "SO", 2))
    {
        directions->so_count++;
        if (!check_path(line+i))
            return false;
    }
    else if (!ft_strncmp(line+i, "WE", 2))
    {
        directions->we_count++;
        if (!check_path(line+i))
            return false;
    }
    else if (!ft_strncmp(line+i, "EA", 2))
    {
        directions->ea_count++;
        if (!check_path(line+i))
            return false;
    }
    else
        return false;
    return true;
}

bool    is_esp_line(char *line)
{
    int i;

    i = 0;
    while (line[i] && line[i] == ' ')
       i++; 
    if (!line[i] || line[i] == '\n')
        return true;
    return false;
}

char *get_line(int fd)
{
    char *line;

    line = get_next_line(fd);
    if (!line)
        return line;
    while (!ft_strncmp(line, "\n", ft_strlen(line)) || is_esp_line(line))
    {
        free(line);
        line = get_next_line(fd); 
        if (!line)
            break;
    }

    return line;
}

char **check_count(char **lines, t_direction dire)
{

    if (dire.no_count != 1)
        return NULL;
    if (dire.ea_count != 1)
        return NULL;
    if (dire.we_count != 1)
        return NULL;
    if (dire.so_count != 1)
        return NULL;

    return lines;
}

static  void    init_struct(t_direction *dire)
{

    dire->no_count = 0;
    dire->ea_count = 0;
    dire->we_count = 0;
    dire->so_count = 0;
}

void    free_memory(char **arr)
{
    int i;

    i = 0;
    while (arr && arr[i])
    {
        // printf("\n line  = %s \n", arr[i]);
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

char    *cpy_line(char *line)
{
   int  i;

   i = 0;
   while (line[i] == ' ')
        i++;
    return ft_strdup(line+i);
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
    init_struct(&dire);
    lines = malloc((sizeof(char*) * 5));
    if (!lines)
        return NULL;
    lines = full_arr(fd, lines,&dire, i);
    if (!check_count(lines, dire))
        return (free_memory(lines),free_getline(fd),NULL);
    return (lines);
}

