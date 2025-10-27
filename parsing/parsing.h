#ifndef PARSING_H
#define PARSING_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./get_next_line/get_next_line.h"

typedef struct s_color_parsing
{
    int count_f;
    int count_c;
} t_count;


typedef struct s_counters
{
	int			count_e;
	int			count_p;
	int			count_c;
	int			count_err;

}				t_counters;

typedef struct s_tmap_info
{
	t_counters	counters;
	char		*line;
	char		**map;
	int			len_next;
	int			len_width;
	int			len_height;
	int			x;
	int			y;
	int			fd;

} t_map_info;

/*utils*/
// size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);
char	*ft_strdup(const char *s);

int open_file(char *file_name, int fd);
/*free*/
void    free_memory(char **arr);
void    free_getline(int fd);

/*check*/
bool    is_esp_line(char *line);
bool	check_file(char *file);
// bool check_line(char *line, t_count *count_color);

char *get_line(int fd);
char    *cpy_line(char *line);

char **diretion_pasing(int fd);
char **color_parsing(char **old_lines, int fd);
char **parsing(char *file_name);
char	**check_input(int fd, char **lines);

#endif