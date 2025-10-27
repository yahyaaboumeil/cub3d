#include <stdio.h>
#include <unistd.h>

#include "./parsing/parsing.h"


int main(int ac, char **av)
{
    // printf("%d\n", ac);
    ac = 2;
    av[1] = "map.cub";
    if (ac == 2)
    {
        parsing(av[1]);
    }
    return 0;
}