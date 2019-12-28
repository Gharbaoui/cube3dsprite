#include "cube.h"

void    draw3dmap(double length, int x, player *pl, int wasvert, double xp, double yp)
{
    static int check;
    double toprojection;
    double wallheight;
    double vheight;
    double height;
    double y;       
    int i = 0;
    int color;

    wallheight = (double)(pl->map->h) / 20;
    color = -1;
    toprojection = (pl->map->w / 2) / tan(30 * M_PI / 180);
    
    vheight = (wallheight * toprojection) / (length);
    if (vheight >= pl->map->h)
        vheight = pl->map->h;
    y = (pl->map->h  - vheight) /  2;

    height = vheight;
    while (++color < y)
        put_pixel(pl->map, x, color, pl->map->txt->celling);
    while (vheight-- > 0)
    {
        color = handel_image_color(wasvert, xp, yp, pl, height, i);
        put_pixel(pl->map, x, y, color);
        i++;
        y++;
    }
    while (y < pl->map->h)
    {
        put_pixel(pl->map, x, y, pl->map->txt->floor);
        y++;
    }

    // sprite test
    double realheight;
    double sheight;

    if (pl->obj[1]->hit && pl->obj[1]->length < length)
    {
        sheight = wallheight;
        realheight = (sheight * toprojection) / pl->obj[1]->length;
        if (realheight > pl->map->h)
            realheight = pl->map->h;
        y = (pl->map->h - realheight) / 2;
        i = 0;
        height = realheight;

        while (realheight-- > 0)
        {
            color = sprite_color(pl, i, height);
            if (color != 0)
                put_pixel(pl->map, x , y, color);
            i++;
            y++;
        }
        // printf("X is %d\n", x);
    }
    

}


int   sprite_color(player *pl, int heightindex, double height)
{
    int yindex, xindex;
    int wx;

    // printf("Offset is %d\n", pl->obj[1]->offset);
    yindex = (heightindex * pl->obj[1]->img.height) / height;
    xindex = (pl->obj[1]->offset * pl->obj[1]->img.width) / pl->obj[1]->width;
    // printf("%d\n",pl->obj[1]->offset);
    return index_in_image(pl->obj[1]->img.xpm[yindex] + (xindex * pl->obj[1]->img.colorchar), pl->obj[1]->img);
}