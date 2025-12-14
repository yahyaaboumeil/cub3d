#include "../parsing.h"

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
char    *cpy_line(char *line)
{
   int  i;

   i = 0;
   while (line[i] == ' ')
        i++;
    return ft_strdup(line+i);
}
