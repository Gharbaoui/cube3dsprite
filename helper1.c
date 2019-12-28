#include "cube.h"

char *line_without_spaces(char *str, int *obj)
{
    int length;
    char *line, *see;
    int i;

    length = (ft_strlen(str) / 2) + 1;
    i = 0;
    line = malloc(length + 1);
    while (i < length)
    {
        line[i] = *str;
        if (*str == '2')
            *obj += 1;
        i++;
        str++;
        if (*str != '\0')
            str++;
    }
    line[i] = '\0';
    return line;
}

void player_pos(player *inf, double speed, char c, double angel)
{
    double x, y;
    if (c == 'D')
    {
        x = inf->x - (cos(angel * M_PI / 180) * speed);
        y = inf->y + (sin(angel * M_PI / 180) * speed);
    }
    else if (c == 'U')
    {
        x = inf->x + (cos(angel * M_PI / 180) * speed);
        y = inf->y - (sin(angel * M_PI / 180) * speed);
    }
    inf->x = x;
    inf->y = y;
}

void    handel_img_memory(player *pl)
{
    pl->img[0] = (image *)malloc(sizeof(image));
    pl->img[1] = (image *)malloc(sizeof(image));
    pl->img[2] = (image *)malloc(sizeof(image));
    pl->img[3] = (image *)malloc(sizeof(image));
}

void    handel_fill_img_structs(player *pl)
{
    int fd1, fd2, fd3, fd4, fd5;

    fd1 = open(pl->map->txt->north, O_RDONLY);
    fill_image_info(pl->img[0], pl->map->txt->north, fd1);

    fd2 = open(pl->map->txt->south, O_RDONLY);
    fill_image_info(pl->img[1], pl->map->txt->south, fd2);

    fd3 = open(pl->map->txt->weast, O_RDONLY);
    fill_image_info(pl->img[2], pl->map->txt->weast, fd3);

    fd4 = open(pl->map->txt->east, O_RDONLY);
    fill_image_info(pl->img[3], pl->map->txt->east, fd4);

    fd5 = open(pl->map->txt->sprite, O_RDONLY);
    fill_image_info(&(pl->obj[1]->img), pl->map->txt->sprite, fd5);
}

void    fill_image_info(image *img, char *filename, int fd)
{
    char *line;

    get_next_line(fd, &line);
    while (!is_digit(*line))
        line++;
    img->width = ft_atoi(&line);
    while (!is_digit(*line))
        line++;
    img->height = ft_atoi(&line);
    while (!is_digit(*line))
        line++;
    img->numcolors = ft_atoi(&line);
    while (!is_digit(*line))
        line++;
    img->colorchar = ft_atoi(&line);
    if (img->numcolors == 1)
        img->numcolors = 1;
    handel_rest_fill_image(img, fd);
    while (1)
    {
        get_next_line(fd, &line);
        if (*line == '\0')
            break ;
    }
}

void    handel_rest_fill_image(image *img, int fd)
{
    int length;
    char *line;
    char *str;
    int i;

    i = -1;
    length = img->numcolors;
    img->strcolor = (char **)malloc(sizeof(char *) * (length + 1));
    img->num = (int *)malloc(sizeof(int) * (length + 1));
    while (++i < length)
    {
        get_next_line(fd, &line);
        line++;
        str = str_cat(&line, 0, img->colorchar, 1);
        img->strcolor[i] = str;
        while (*line != '#')
            line++;
        line++;
        img->num[i] = handel_hex(line);
    }
    img->strcolor[i] = NULL;
    img->num[i] = -1;
    fill_xpm(img, fd);
}

void    fill_xpm(image *img, int fd)
{
    char *line;
    int i;
    int length;
    int len;
    
    length = img->height;
    len = img->width * img->colorchar;
    i = -1;
    get_next_line(fd, &line);
    img->xpm = (char **)malloc(sizeof(char *) * (length + 1));
    while (++i < length)
    {
        get_next_line(fd, &line);
        line++;
        line[len] = '\0';
        img->xpm[i] = line;
    }
    img->xpm[i] = NULL;
}