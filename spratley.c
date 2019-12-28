#include "cube.h"

int     is_digit(char c)
{
    return ((c >= '0' && c <= '9') ? 1 : 0);
}

int     ft_atoi(char **numstr)
{
    char *str;
    int num;

    num = 0;
    str = *numstr;
    while (is_digit(*str))
        num = (num * 10) + (*str++ - 48);
    *numstr = str;
    return (num);
}

int     str_cmp(char *s1, char **s2, int len, int ismaoveable)
{
    char *str;

    str = *s2;
    while (*s1 && *str && len--)
    {
        if (*s1 != *str)
            return (0);
        s1++;
        str++;
    }
    if (ismaoveable)
        *s2 = str;
    return 1;
}

char    *str_cat(char **line, int isfree, int len, int ismoveable)
{
    char *str;
    char *tmp;
    int i;

    i = 0;
    
    str = *line;
    if (isfree)
        while (*str == ' ' && ++i)
            str++;
    tmp = malloc((len - i) + 1);
    i = -1;
    while (str[++i] && i < len)
        tmp[i] = str[i];
    tmp[i] = '\0';
    if (ismoveable)
        *line = &str[i];
    return (tmp);
}

int     rgb_to_int(char *str)
{
    int r, g, b;
    int ret;

    while (*str == ' ')
        str++;
    r = ft_atoi(&str);
    str++;
    g = ft_atoi(&str);
    str++;
    b = ft_atoi(&str);
    ret = ((256 * 256) * r) + (256 * g) + b;
    return (ret);
}

void    handel_resolution(map_inf *inf, char **l)
{
    char *line;

    line = *l;
    while (!is_digit(*line))
        line++;
    inf->w = ft_atoi(&line);
    while (!is_digit(*line))
        line++;
    inf->h = ft_atoi(&line);
    free(*l);
}


void    put_pixel(map_inf *map, int x, int y, int color)
{
    int k;
    int *data;

    data = (int *)mlx_get_data_addr(map->img_ptr, &k, &k, &k);
    data[(y * map->w) + x] = color;
}

int can_move(player *pl, char c, double speed)
{
    double x , y;
    point hit;
    if (c == 'U')
    {
        x = pl->x + (cos(pl->look * M_PI / 180) * speed);
        y = pl->y - (sin(pl->look * M_PI / 180) * speed);
    }
    else if (c == 'D')
    {
        x = pl->x - (cos(pl->look * M_PI / 180) * speed);
        y = pl->y + (sin(pl->look * M_PI / 180) * speed);
    } 
    return !(is_there_wall(pl->map, x, y, &hit));
}

int is_there_wall(map_inf *map, double x, double y, point *hitpos)
{
    int xindex, yindex;
    xindex = (int)(x / map->width);
    yindex = (int)(y / map->height);
    if (map->map_lines[yindex][xindex] == '1')
        return (1);
    else if (map->map_lines[yindex][xindex] == '2')
    {
        hitpos->x = (xindex * map->width) + (map->width / 2);
        hitpos->y = (yindex * map->height) + (map->height / 2);
        return 2;
    }
    return (0);
}

double handel_angel(double angel)
{
    int ang;
    double reangel, smalltip;
    ang = (int)angel;
    smalltip = angel - (double)ang;
    ang = (ang + 360) % 360;
    reangel = (double)ang + smalltip;
    return (reangel);
}

void ray_dirction(dirction *dir, double angel)
{
    dir->strightup = dir->strightdown = 0;
    dir->strightleft = dir->strightright = 0;
    dir->up = dir->down = 0;
    dir->right = dir->left = 0;
    dir->spech = 1;
    if (angel == 90)
        dir->strightup = 1;
    else if (angel == 270)
        dir->strightdown = 1;
    else if (angel == 0)
        dir->strightright = 1;
    else if (angel == 180)
        dir->strightleft = 1;
    else
    {
        if (angel > 0 && angel < 180)
            dir->up = 1;
        else if (angel > 180 && angel < 360)
            dir->down = 1;
        if ((angel > 270 && angel <= 360) || (angel >= 0 && angel < 90))
            dir->right = 1;
        else if ((angel > 90 && angel < 270))
            dir->left = 1;
        dir->spech = 0;
    }
    dir->wasvert = 0;
    dir->angel = angel;
}

void    handel_ypos_dx(double *ypos, double *dx, player *pl, dirction dir)
{
    (*ypos) = (int)pl->y - ((int)pl->y % pl->map->height);
    (*ypos) += (dir.down || dir.strightdown) ? pl->map->height : 0;
    (*dx) = (!dir.spech) ? (pl->y - (*ypos)) / tan(dir.angel * M_PI / 180) : 0;
    (*dx) *= (dir.right && (*dx) < 0) ? -1 : 1;
    (*dx) *= (dir.left && (*dx) > 0) ? -1 : 1;
    (*ypos) -= (dir.up || dir.strightup) ? 1 : 0;
}

double calculate_length(double x1, double y1, double x2, double y2)
{
    double length;
    double dx;
    double dy;
    dx = ((x2 - x1) * (x2 - x1));
    dy = ((y1 - y2) * (y1 - y2));
    length  = sqrt(dx + dy);
    return (length);
}