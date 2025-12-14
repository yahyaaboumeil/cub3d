#ifndef PARSING_H
#define PARSING_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./get_next_line/get_next_line.h"

typedef struct s_dire_parsing
{
    int no_count;
    int so_count;
    int we_count;
    int ea_count;

} t_direction;

typedef struct s_color_parsing
{
    int count_f;
    int count_c;
} t_count;


typedef struct s_counters
{
	int			count_p;
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

typedef struct s_data
{
   char *north_path;
   char *east_path;
   char *south_path;
   char *west_path;
   int f_color[2];
   int c_color[2];
   int	x;
   int	y;
   int width;
   int hight;	
   char **map;
} t_data;

/*utils*/
// size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);
char	*ft_strdup(const char *s);
int skip_ind_space(char *line);
char	**ft_split(char const *s, char c);

int open_file(char *file_name, int fd);

/*free*/
void    free_memory(char **arr);
void    free_getline(int fd);
void free_struct(t_data *data);

/*check*/
bool    is_esp_line(char *line);
bool	check_file(char *file);
bool check_line(char *line, t_direction *directions);
bool    check_path(char *line);
char **check_count(char **lines, t_direction dire);
bool check_map_line(int fd, char *line, t_counters *counters, char **lines);
char	**check_input(int fd, char **lines);
int	last_non_newline_index(const char *line);
bool check_if_can_play_in_map(char **map);
bool check_map_line(int fd, char *line, t_counters *counters, char **lines);

// bool check_line(char *line, t_count *count_color);

char *get_line(int fd);
char    *cpy_line(char *line);

char **diretion_pasing(int fd);
char **color_parsing(char **old_lines, int fd);
char **add_line(char *line, char **lines);

t_data *parsing(char *file_name);
//count
t_counters init(t_counters *counters);
int skip_espas(char *line);
int count(char **lines);

void err_map(int fd, char *line, char **lines);
char **check_err(int fd, t_counters counters, char *line, char **lines);

t_counters init(t_counters *counters);
int count(char **lines);

#endif
