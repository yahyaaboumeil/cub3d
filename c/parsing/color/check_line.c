#include "../parsing.h"

static int is_number(char *str)
{
    int i = 0;
    if (!str || !*str)
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static bool check_rgb_value(char *str)
{
    int value;

    if (*(str+(ft_strlen(str)-1)) == '\n')
        *(str+(ft_strlen(str)-1)) = 0;
    if (!is_number(str))
        return (false);
    value = ft_atoi(str);
    if (value < 0 || value > 255)
        return (false);
    return (true);
}
void free_split(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

static t_data *save_color(t_data *data, char type, t_count *count, char *line)
{
   char **split;

   split = NULL;
	   
   if (type == 'f')
   {
	   if (count->count_f != 1)
		return (free_struct(data), NULL);	
	   split = ft_split(ft_strchr(line , 'F'), ',');
	   data->f_color[0] = atoi(split[0]);
	   data->f_color[1] = atoi(split[1]);
	   data->f_color[2] = atoi(split[2]);
   }
   else
   {
	   if (count->count_c != 1)
		   return (free_struct(data), NULL);	
	   split = ft_split(ft_strchr(line , 'C'), ',');
	   data->c_color[0] = atoi(split[0]);
	   data->c_color[1] = atoi(split[1]);
	   data->c_color[2] = atoi(split[2]);
   }
   free_memory(split);
   return data;
}

bool check_line2(t_data *data, char *line, t_count *count_color)
{
    char **split;
    char *content;
    int   parts = 0;
    char type;

    while (*line == ' ')
        line++;
    if (*line == 'F')
    {
        (1) && (count_color->count_f++, content = line + 1);
	type = 'f';
    }
    else if (*line == 'C')
    {
        (1) && (count_color->count_c++, content = line + 1);
	type = 'c';
    }

    else
        return (false);
    while (*content == ' ')
        content++;
    split = ft_split(content, ',');
    while (split && split[parts])
        parts++;
    if (parts != 3 || !check_rgb_value(split[0]) || !check_rgb_value(split[1]) || !check_rgb_value(split[2]))
    {
        printf("Error\nInvalid color format: %s\n", line);
        return (free_split(split), false);
    }
    data = save_color(data, type, count_color, line); 
    if (!data)
	    return (free_split(split), false);
    return (free_split(split), true);
}
