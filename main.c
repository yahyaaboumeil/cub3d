#include <stdio.h>
#include <unistd.h>

#include "./parsing/parsing.h"
#include "./execution/cub3d.h"


int main(int ac, char **av)
{
    if (ac == 2)
    {
        t_data *data = parsing(av[1]);
        if (!data)
            return 1;
        play(data);
    }
    return 0;
}
