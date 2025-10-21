#ifndef PARSING_H
#define PARSING_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include "./get_next_line/get_next_line.h"

/*utils*/
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);


/*check*/
int	check_file(char *file);


char **parsing(char *file_name);

#endif