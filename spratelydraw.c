#include "cube.h"

void    draw_maze(player *pl)
{
    int i;
    char **linesmap;

    pl->x = 0;
    pl->y = 0;
    pl->look = -10;
    linesmap = pl->map->map_lines;
    i = -1;
    while (linesmap[++i] && pl->look == -10)
        draw_one_line(linesmap[i], pl, i);
}

void    handel_look_player(char *c, player *pl, int j, int lineindex)
{
    double x, y;
    x = pl->x;
    y = pl->y;
    char *str;
    if (*c == 'N')
        pl->look = 90;
    else if (*c == 'S')
        pl->look = 270;
    else if (*c == 'W')
        pl->look = 180;
    else
        pl->look = 0;
    pl->x += pl->map->width / 2;
    pl->y += pl->map->height / 2;
    while (*c)
    {
        if (*c == '2')
        {
            pl->obj[j]->pos.x = x + (pl->map->width / 2);
            pl->obj[j]->pos.y = y + (pl->map->height / 2);
            j++;
        }
        x += pl->map->width;
        c++;
    }
    x = 0;
    y += pl->map->height;
    lineindex++;
    rest_pos_sprite(pl, lineindex, y, j);
    draw_player(pl);
}

void    draw_player(player *pl)
{
    rayhit *hit;
    double width;
    int pcounter;
    double toadd;
    double xp;
    int i = -1;
    double yp;
    double angel;
    double length;
    double x;
    int wasvert;

    x = -1;
    pcounter = 0;
    width = (double)pl->map->w;
    toadd = 60.0 / width;
    angel = pl->look + 30;
    while (++x < width)
    {
        length = raycasting(pl, angel, &xp, &yp, &wasvert) * cos((pl->look - angel) * M_PI / 180);
        draw3dmap(length, x, pl, wasvert, xp, yp);
        angel -= toadd;
    }
    i = -1;
}

void    draw_one_line(char *line, player *pl, int lineindex)
{
    int i;
    static int check;
    static int j;
    i = -1;
    while (line[++i] && !check)
    {
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
            return handel_look_player(line + i, pl, j, lineindex);
        else if (line[i] == '2')
        {
            pl->obj[j]->pos.x = pl->x + (pl->map->width / 2);
            pl->obj[j]->pos.y = pl->y + (pl->map->height / 2);
            j++;
        }
        pl->x += pl->map->width;
    }
    pl->x = 0;
    pl->y += pl->map->height;
}

int     update_scene(int key, player *pl)
{
    double speed;

    speed = 25.0;
    pl->look = ((int)pl->look + 360) % 360;
    if (key == 2 || key == 124)
        pl->look = ((int)pl->look) - 10;
    else if (key == 0 || key == 123)
        pl->look = ((int)pl->look) + 10;
    else if (key == 13 || key == 126)
    {
        if (can_move(pl, 'U', speed))
           player_pos(pl, speed, 'U', pl->look);
    }
    else if (key == 1|| key == 125)
    {
        if (can_move(pl, 'D', speed))
             player_pos(pl, speed, 'D', pl->look);
    }
    mlx_destroy_image(pl->map->mlx_ptr, pl->map->img_ptr);
    mlx_clear_window(pl->map->mlx_ptr, pl->map->win_ptr);
    pl->map->img_ptr = mlx_new_image(pl->map->mlx_ptr, pl->map->w,pl->map->h);
    draw_player(pl);
    mlx_put_image_to_window(pl->map->mlx_ptr, pl->map->win_ptr, pl->map->img_ptr, 0,0);
    return 0;
}

