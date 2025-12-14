#include "parsing.h"


static t_data *save_path(t_data *data, char **arr)
{
   int i;

   i = -1;
   while (++i < 4)
   {
      if (ft_strncmp(arr[i], "NO", 2) == 0)
         data->north_path = ft_strdup(ft_strchr(arr[i], '.'));
      else if (ft_strncmp(arr[i], "SO", 2) == 0)
         data->south_path = ft_strdup(ft_strchr(arr[i], '.'));
      else if (ft_strncmp(arr[i], "WE", 2) == 0)
         data->west_path = ft_strdup(ft_strchr(arr[i], '.'));
      else if (ft_strncmp(arr[i], "EA", 2) == 0)
         data->east_path = ft_strdup(ft_strchr(arr[i], '.'));  
   }
   return data;
}

static t_data *save_color(t_data *data, char **arr, int index)
{
   char **split;
   
   split = NULL;
   if (ft_strchr(arr[index], 'F'))
   {
      split = ft_split(ft_strchr(arr[index] , 'F'), ',');
      data->f_color[0] = atoi(split[0]);
      data->f_color[1] = atoi(split[1]);
      data->f_color[2] = atoi(split[2]);
   }
   else
   {
      split = ft_split(ft_strchr(arr[index] , 'C'), ',');
      data->c_color[0] = atoi(split[0]);
      data->c_color[1] = atoi(split[1]);
      data->c_color[2] = atoi(split[2]);
   }
   free_memory(split);
   return data;
}


void  save_x_y(t_data *d)
{
   int   i;
   int   j;

   i = 0;
   j = 0;
   while (d->map[i])
   {
      while (d->map[i][j])
      {
         if (d->map[i][j] == 'N' || d->map[i][j] == 'S' || d->map[i][j] == 'W' || d->map[i][j] == 'E')
         {
            d->x = i;
            d->y = j;
            return;
         }
         j++;
      }
      j = 0;
      i++;
   }
   j = 0;
   i = 0;
   while(d->map[i])
   {
      while(d->map[i][j++]);
      d->width = j;
      i++;
      j = 0;
   }
   d->hight = i - 1;
}

t_data *convert_arr_to_struct(char **arr)
{
   t_data *data;
   int i;

   data = malloc(sizeof(t_data));

   data = save_path(data, arr);

   data = save_color(data, arr, 4);
   data = save_color(data, arr, 5);

   i = 6;
   while (arr[i])
      i++;
   data->map = malloc(sizeof(char *) * (i + 1));
   i = 6;
   while (arr[i])
   {
      data->map[i - 6] = ft_strdup(arr[i]);
      i++;
   }
   data->map[i - 6] = NULL;
   save_x_y(data);
   free_memory(arr);
   return data;
}



t_data *parsing(char *file_name)
{
   int fd;

   fd = 0;
   if (!check_file(file_name))
        return (printf("\nError/nthe file should be file.cub\n"), NULL);
   fd = open_file(file_name, fd);
   if (fd == -1)
      return (printf("\nError\nCannot open file\n"), NULL);
   char **lines = diretion_pasing(fd); 
   if (!lines)
        return (printf("\nError\nthere is unexiste path\n"), NULL);
   lines = color_parsing(lines, fd);
   if (!lines)
        return (printf("\nError\nthere is err in the color information\n"), NULL);
   lines  = check_input(fd, lines);
   t_data *data = convert_arr_to_struct(lines);
   if (!check_if_can_play_in_map(data->map))
      return (printf("\nError\nthe map is not suitable for play\n"), free_struct(data), NULL);
   return data;
}
