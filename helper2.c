#include "cube.h"

int handel_hex(char *str)
{
    int num;
    int i = 5;
    int multbase;

    num = 0;
    multbase = 1;
    while (i >= 0)
    {
        if (str[i] >= '0' && str[i] <= '9')
            num += (str[i] - 48) * multbase;
        else if (str[i] >= 'A' && str[i] <= 'Z')
            num += (str[i] - 55) * multbase;
        else if (str[i] >= 'a' && str[i] <= 'z')
            num += (str[i] - 87) * multbase;
        multbase *= 16;
        i--;
    }
    return num;
}

int     handel_image_color(int wasvert, double xp, double yp, player  *pl, double height, int heightindex)
{
    int index, wy, yindex, wx;
    int i;

    if (wasvert)
    {
        if (xp > pl->x)
            i = 1;
        else
            i = 2;
        yindex = (heightindex * pl->img[i]->height) / height;
        wy = ((int)yp % pl->map->height);
        index = (wy * pl->img[i]->width) / pl->map->height;
    }
    else
    {
        if (yp > pl->y)
            i = 0;
        else
            i = 3;
        yindex = (heightindex * pl->img[i]->height) / height;
        wx = ((int)xp % pl->map->width);
        index = (wx * pl->img[i]->width) / pl->map->width;
    }
    return index_in_image(pl->img[i]->xpm[yindex] + (index * pl->img[i]->colorchar), *(pl->img[i]));
}

int     index_in_image(char *line, image img)
{
    int i;

    i = -1;
    while (++i < img.numcolors)
        if (str_cmp(line, &(img.strcolor[i]), img.colorchar, 0))
            return img.num[i];
    return 0xffffff;
}