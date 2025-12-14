#include "color.h"

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

bool check_line2(char *line, t_count *count_color)
{
    char **split;
    char *content;
    int   parts = 0;

    while (*line == ' ')
        line++;
    if (*line == 'F')
        (1) && (count_color->count_f++, content = line + 1);
    else if (*line == 'C')
        (1) && (count_color->count_c++, content = line + 1);
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
    return (free_split(split), true);
}
