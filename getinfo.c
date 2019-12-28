#include "cube.h"

int    fill_map_struct(map_inf *map, char *mapname)
{
    int fd;
    char *line;
    int i;
    int objs;
    int length;

    i = 0;
    map->txt = (texture *)malloc(sizeof(texture));
    fd = open(mapname, O_RDONLY);
    get_next_line(fd, &line);
    handel_resolution(map, &line);
    get_next_line(fd, &line);
    while (i < 7)
    {
        if ((str_cmp("NO", &line, 2, 0) || str_cmp("SO", &line, 2, 0) || str_cmp("WE", &line, 2, 0)) && ++i)
            handel_texture((map->txt), &line, 1);
        else if ((str_cmp("EA", &line, 2, 0) || str_cmp("S", &line, 1, 0)) && ++i)
            handel_texture(map->txt, &line, 2);
        else if ((str_cmp("C", &line, 1, 0) || str_cmp("F", &line, 1, 0)) && ++i)
            handel_texture(map->txt, &line, 3);
        get_next_line(fd, &line);
    }
    length = count_height_map(map, fd, line);
    fd = open(mapname, O_RDONLY);
    map->map_lines = (char **)malloc(sizeof(char *) * map->map_heigth + 1);
    objs = fill_map_lines(&map->map_lines, map->map_heigth, length, fd);
    return (objs + 1);
}

int    fill_map_lines(char ***line, int height, int length, int fd)
{
    char *str;
    int i;
    int obj;

    i = -1;
    obj = 0;
    get_next_line(fd, &str);
    while (*str != '1')
        get_next_line(fd, &str);
    while (++i < height)
    {
        *(*line + i) = line_without_spaces(str, &obj);
        get_next_line(fd, &str);
    }
    *(*line + i) = NULL;
    return obj;
}

int    count_height_map(map_inf *map, int fd, char *line)
{
    int i;
    int length;

    i = 1;
    length = ((ft_strlen(line) / 2) + 1);
    map->width = map->w / length;
    while (1)
    {
        get_next_line(fd, &line);
        if (*line == '\0')
            break ;
        i++;
    }
        
    map->map_heigth = i;
    map->height = map->h / i;
    return (length);
}

void    handel_texture(texture *txt, char **line, int flag)
{
    char *str;

    str = *line;
    if (flag == 1)
    {
        if ((str_cmp("NO", &str, 2, 1)))
            txt->north = str_cat(&str, 1, ft_strlen(str), 0);
        else if ((str_cmp("SO", &str, 2, 1)))
            txt->south = str_cat(&str, 1, ft_strlen(str), 0);
        else if ((str_cmp("WE", &str, 2, 1)))   
            txt->weast =  str_cat(&str, 1, ft_strlen(str), 0);
    }
    else if (flag == 2)
    {
        if (str_cmp("EA", &str, 2, 1))
            txt->east = str_cat(&str, 1, ft_strlen(str), 0);
        else if (str_cmp("S", &str, 1, 1))
            txt->sprite = str_cat(&str, 1, ft_strlen(str), 0);
    }
    else if (flag == 3)
    {
        if (str_cmp("C", &str, 1, 1))
            txt->celling = rgb_to_int(str);
        else if (str_cmp("F", &str, 1, 1))
            txt->floor = rgb_to_int(str);
    }
    free(*line);
}