#include "cube.h"

void    rest_pos_sprite(player *pl, int lineindex, double y, int j)
{
    char **line, *str;
    int fd;
    double x;

    line = pl->map->map_lines;
    while (line[lineindex])
    {
        x = 0;
        str = line[lineindex];
        while (*str)
        {
            if (*str == '2')
            {
                pl->obj[j]->pos.x = x + (pl->map->width / 2);
                pl->obj[j]->pos.y = y + (pl->map->height / 2);
                j++;
            }
            x += pl->map->width;
            str++;
        }
        lineindex++;
        y += pl->map->height;
    }
    pl->obj[j]->pos.x = -1;
    pl->obj[j]->pos.y = -1;
}

int     is_in_range(double xinter,double yinter, double left, double right, double up, double down)
{
    if (xinter >= left && xinter <= right && yinter > up && yinter < down)
        return 1;
    return 0;
}

double sprite_length(line spline, double yup, double ydown, double left, double right)
{
    double length_h, length_v;
    point interup, interdown, interleft, interright;

    interup.y = yup;
    interup.x = (interup.y - spline.c) / spline.slope;

    interdown.y = ydown;
    interdown.x = (interdown.y - spline.c) / spline.slope;
    length_h = calculate_length(interup.x, interup.y, interdown.x, interdown.y);
    interleft.x = left;
    interleft.y = (left * spline.slope) + spline.c;

    interright.x = right;
    interright.y = (right * spline.slope) + spline.c;
    length_v = calculate_length(interleft.x, interleft.y, interright.x, interright.y);
    if (length_v > length_h)
        return length_h;
    return length_v;
}