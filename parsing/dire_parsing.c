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

char *check_line(char *line)
{
    if (ft_strncmp(line, "NO", 2))
    {
        
    } 
    else if (ft_strncmp(line, "SO", 2))
    {

    }
    else if (ft_strncmp(line, "WE", 2))
    {
        
    }
    else if (ft_strncmp(line, "EA", 2))
    {

    }
}


char **diretion_pasing(char *file_name)
{
    int fd;
    char *line;
    char **lines;

    line = NULL;
    fd = open_file(file_name, fd);
    if (fd == -1)
    {
        printf("\nError\nCannot open file\n");
        return NULL;
    }
    line = get_next_line(fd); 

}
